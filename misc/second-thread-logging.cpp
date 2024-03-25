#include <array>
#include <cstring>
#include <deque>
#include <iostream>
#include <span>
#include <mutex>
#include <atomic>
#include <thread>
#include <latch>

#ifdef __cpp_lib_hardware_interference_size
static constexpr auto constructiveInterference =  std::hardware_constructive_interference_size;
static constexpr auto destructiveInterference = std::hardware_destructive_interference_size;
#else
// 64 bytes on x86-64 │ L1_CACHE_BYTES │ L1_CACHE_SHIFT │ __cacheline_aligned │ ...
static constexpr std::size_t constructiveInterference =  64;
static constexpr std::size_t destructiveInterference = 64;
#endif

template<typename T>
std::span<T, 1> singular_span(T& t)
{
    return std::span<T, 1>{std::addressof(t), 1};
}

template<typename T>
auto singular_bytes(T& t)
{
    return std::as_bytes(singular_span(t));
}

template<typename T>
auto singular_writable_bytes(T& t)
{
    return std::as_writable_bytes(singular_span(t));
}


// This is a rather dumb container, but it will work for most
// of our tests.
template<std::size_t N = std::dynamic_extent>
class SpanBuffer {

	alignas(destructiveInterference) std::atomic<std::ptrdiff_t> head_{0};
	alignas(destructiveInterference) std::ptrdiff_t cachedHead_{0};

	alignas(destructiveInterference) std::atomic<std::ptrdiff_t> tail_{0};
	alignas(destructiveInterference) std::ptrdiff_t cachedTail_{0};


	alignas(destructiveInterference) std::ptrdiff_t shadowHead_{0};
	alignas(destructiveInterference) std::ptrdiff_t shadowTail_{0};

	std::span<std::byte, N> buf_;

	[[nodiscard]]  constexpr bool can_write(const std::ptrdiff_t sz, const std::ptrdiff_t bufSz) const {
		if (shadowTail_ < cachedHead_)
			return sz < (cachedHead_ - shadowTail_);
		else
			return sz <= (bufSz - shadowTail_);
	}

	[[nodiscard]]  constexpr bool can_read(const std::ptrdiff_t sz) const {
		return sz <= (cachedTail_ - shadowHead_);
	}

public:
	
	SpanBuffer(std::span<std::byte, N> data, bool filled) : buf_{data} {
		if (filled)
			tail_ = static_cast<std::ptrdiff_t>(data.size_bytes());
	}

	SpanBuffer(SpanBuffer&& other) 
	: head_{other.head_.load()}
	, cachedHead_{other.cachedHead_}
	, tail_{other.tail_.load()}
	, cachedTail_{other.cachedTail_}
	, shadowHead_{other.shadowHead_}
	, shadowTail_{other.shadowTail_}
	, buf_{std::move(other.buf_)}
	{

	}

	bool read(std::span<std::byte> dst) {
		const auto sz = static_cast<std::ptrdiff_t>(dst.size_bytes());

		if (!can_read(sz)) {
			cachedTail_ = tail_.load(std::memory_order::acquire);
			if (!can_read(sz))
				return false;
		}

		std::memcpy(dst.data(), buf_.data() + shadowHead_, dst.size_bytes());
		shadowHead_ += dst.size_bytes();

		return true;
	}

	bool write(std::span<const std::byte> src) {
		const auto sz = static_cast<std::ptrdiff_t>(src.size_bytes());
		const auto bufSz = static_cast<std::ptrdiff_t>(buf_.size_bytes());
		// ok, so let's write a test here. It's going to be painful, but let's
		// do it.

		if (!can_write(sz, bufSz)) {
			cachedHead_ = head_.load(std::memory_order::acquire);
			if (!can_write(sz, bufSz))
				return false;
		}

		std::memcpy(buf_.data() + shadowTail_, src.data(), src.size_bytes());
		shadowTail_ += src.size_bytes();

		return true;
	}
	
	// It's a noop for us for now.
	void start_read() {
		// ok, so we are initializing a read here.
		shadowHead_ = head_.load(std::memory_order::relaxed);

		if (cachedTail_ < shadowHead_) {
			shadowHead_ = 0;
			head_.store(0, std::memory_order::relaxed);
		}
	}

	void finish_read() {
		head_.store(shadowHead_, std::memory_order::release);
	}

	void cancel_read() {}
	
	void start_write() {
		shadowTail_ = tail_.load(std::memory_order::relaxed);

		if (cachedHead_ == shadowTail_ && shadowTail_ != 0) {
			// First we store the tail behind.
			shadowTail_ = 0;
			tail_.store(0, std::memory_order::relaxed);
		}

		// Ok, so this is where things get interesting. if our cached head is
		// where we are, then it means they cached up to us. this means they 
		// will not be able to progress before it's their turn. We will therefor
		// wait.
	}

	void finish_write() {
		// Now let's update the tail_
		tail_.store(shadowTail_, std::memory_order::release);
	}

	void cancel_write() {}
};

// additional deduction guide
template<std::size_t N>
SpanBuffer(std::array<std::byte,N> data, bool filled) -> SpanBuffer<N>;

// This is a rather dumb container, but it will work for most
// of our tests.
template<std::ptrdiff_t N>
class RingBuffer {

	alignas(destructiveInterference) std::atomic<std::ptrdiff_t> head_{0};
	alignas(destructiveInterference) std::ptrdiff_t cachedHead_{0};

	alignas(destructiveInterference) std::atomic<std::ptrdiff_t> tail_{0};
	alignas(destructiveInterference) std::ptrdiff_t cachedTail_{0};


	alignas(destructiveInterference) std::ptrdiff_t shadowHead_{0};
	alignas(destructiveInterference) std::ptrdiff_t shadowTail_{0};

	alignas(destructiveInterference) std::array<std::byte, N+1> buf_;

	[[nodiscard]]  constexpr bool can_write(const std::ptrdiff_t sz) const {
		if (shadowTail_ < cachedHead_)
			return sz < (cachedHead_ - shadowTail_);
		else
			return sz <= (N - shadowTail_);
	}

	[[nodiscard]]  constexpr bool can_read(const std::ptrdiff_t sz) const {
		return sz <= (cachedTail_ - shadowHead_);
	}

public:
	RingBuffer() = default;
	
	// We don't want copying
	RingBuffer(const RingBuffer&) = delete;
	RingBuffer& operator=(const RingBuffer&) = delete;

	// We don't want moving either.
	RingBuffer(RingBuffer&&) = delete;
	RingBuffer& operator=(RingBuffer&&) = delete;

	bool read(std::span<std::byte> dst) {
		while (!dst.empty()) {
			const auto sz = static_cast<std::ptrdiff_t>(dst.size_bytes());
			if (shadowHead_ == N+1)
				shadowHead_ = 0;


			if (shadowHead_ == cachedTail_) {
				cachedTail_ = tail_.load(std::memory_order::acquire);
				if (shadowHead_ == cachedTail_)
					return false;
			}

			if (shadowHead_ < cachedTail_) {
				const auto spaceLeft = cachedTail_ - shadowHead_;
				const auto readSize = std::min(sz, spaceLeft);
				
				std::memcpy(dst.data(), buf_.data() + shadowHead_, static_cast<std::size_t>(readSize));
				shadowHead_ += readSize;

				dst = dst.subspan(static_cast<std::size_t>(readSize));
			} else {
				const auto spaceLeft = N+1 - shadowHead_;
				const auto readSize = std::min(sz, spaceLeft);

				std::memcpy(dst.data(), buf_.data() + shadowHead_, static_cast<std::size_t>(readSize));
				shadowHead_ += readSize;

				dst = dst.subspan(static_cast<std::size_t>(readSize));
			}
		}

		return true;
	}

	bool write(std::span<const std::byte> src) {
		/* std::cout << "we entered with: " << cachedHead_ << " and tail=" << shadowTail_ << std::endl; */
		// as we might have to do multiple jumps, we calculate to begin with.
		while (!src.empty()) {
			const auto sz = static_cast<std::ptrdiff_t>(src.size_bytes());

			if (shadowTail_ == N+1) {
				if (cachedHead_ == 0) {
					cachedHead_ = head_.load(std::memory_order::acquire);
					if (cachedHead_ == 0)
						return false;
				}
				shadowTail_ = 0;
			} else if (shadowTail_+1 == cachedHead_) {
				cachedHead_ = head_.load(std::memory_order::acquire);
				if (shadowTail_+1 == cachedHead_)
						return false;
			}

			if (cachedHead_ <= shadowTail_) {
				const auto spaceLeft = N+1 - shadowTail_;
				const auto writeSize = std::min(sz, spaceLeft);
				
				std::memcpy(buf_.data() + shadowTail_, src.data(), static_cast<std::size_t>(writeSize));
				shadowTail_ += writeSize;

				src = src.subspan(static_cast<std::size_t>(writeSize));
			} else {
				// In this regard, the tail is behind the head
				const auto spaceLeft = cachedHead_ - shadowTail_ - 1;
				const auto writeSize = std::min(sz, spaceLeft);

				std::memcpy(buf_.data() + shadowTail_, src.data(), static_cast<std::size_t>(writeSize));
				shadowTail_ += writeSize;

				src = src.subspan(static_cast<std::size_t>(writeSize));
			}
		}
	
		/* std::cout << "we managed to write!" << std::endl; */
		return true;
	}
	
	// It's a noop for us for now.
	void start_read() { shadowHead_ = head_.load(std::memory_order::relaxed); }
	void finish_read() { head_.store(shadowHead_, std::memory_order::release); }
	void cancel_read() {}
	
	void start_write() { shadowTail_ = tail_.load(std::memory_order::relaxed); }
	void finish_write() { tail_.store(shadowTail_, std::memory_order::release); }
	void cancel_write() {}
};



class QueueBuffer {
	std::mutex mtx_;
	std::deque<std::byte> q_;

	decltype(q_)::iterator readLevel_;
	decltype(q_)::iterator writeLevel_;
public:

	bool read(std::span<std::byte> dst) {
		if (std::distance(readLevel_, q_.end()) < static_cast<std::ptrdiff_t>(dst.size_bytes()))
			return false;

		const auto first = readLevel_;
		const auto end = std::next(readLevel_, static_cast<std::ptrdiff_t>(dst.size_bytes()));

		std::copy(first, end, dst.begin());

		readLevel_ = end;
		return true;
	}

	bool write(std::span<const std::byte> src) {
		q_.insert(q_.end(), src.begin(), src.end());
		return true;
	}

	void start_read() {
		mtx_.lock();
		readLevel_ = q_.begin();
	}
	void finish_read() {
		q_.erase(q_.begin(), readLevel_);
		mtx_.unlock();
	}
	void cancel_read() {
		mtx_.unlock();
	}


	void start_write() {
		mtx_.lock();
		writeLevel_ = q_.end();
	}
	void finish_write() {
		mtx_.unlock();
	}

	void cancel_write() {
		q_.erase(writeLevel_, q_.end());
		mtx_.unlock();
	}
};

template <typename BufferType, typename T, typename = void>
struct Serializer;

template<typename BufferType, typename T>
struct Serializer<BufferType, T, std::enable_if_t<std::is_scalar_v<T>>> {
	bool to_bytes(BufferType& buffer, const T& val) {
		return buffer.write(singular_bytes(val));
	};

	bool from_bytes(BufferType& buffer, T& val) {
		return buffer.read(singular_writable_bytes(val));
	}
};

template<typename BufferType, typename T>
struct Serializer<BufferType, T, std::enable_if_t<std::is_convertible_v<T, std::string_view>>> {
	bool to_bytes(BufferType& buffer, std::string_view val) {
		bool good = true;
		good = good && write_to_buffer(buffer, val.size());
		good = good && buffer.write(std::as_bytes(std::span(val.begin(), val.end())));
		return good;
	};

	// TODO(rHermes): Decode what I want to do here. Should the value here be
	// accessable?
	bool from_bytes(BufferType& buffer, std::string& val) {
		std::string_view::size_type sz;
		if (!read_from_buffer(buffer, sz))
			return false;

		val.resize(sz);
		return buffer.read(std::as_writable_bytes(std::span(val.begin(), val.end())));
	}
};

template<typename T, typename BufferType>
bool write_to_buffer(BufferType& buff, const T& src) {
	Serializer<BufferType, T> ser;
	return ser.to_bytes(buff, src);
}

template<typename T, typename BufferType>
bool read_from_buffer(BufferType& buff, T& src) {
	Serializer<BufferType, T> ser;
	return ser.from_bytes(buff, src);
}

// Unsafe version of above
template<typename T, typename BufferType>
T read_from_buffer(BufferType& buff) {
	T lel{};
	Serializer<BufferType, T> ser;
	ser.from_bytes(buff, lel);
	return lel;
}


// It is important to note, that this logger is fundamentally
// multithreaded, and it's built around the idea of there being
// one produser and once consumer. this means th
template <typename Buffer>
class Logger {
	Buffer buffer_{};
	// OK, so the optimalization I want to implement here, is that we should only update the reader
	// fields, once we are completly done. But this is turning out to be ultra hard, so I'm not sure I like it.
	// How could I mock this out. I would need something that holds that lock inside the buffer, if we
	// are passing in a Writer. So we need to create both a reader and a buffer on the same thing.
	
	std::atomic_unsigned_lock_free available_{0};
	
public:
	using loggingFunction = std::add_pointer_t<bool(Buffer&)>;

	Logger() {}
	Logger(Buffer buff) : buffer_{std::move(buff)} {}

	
	template <typename ... Ts>
	bool try_log(loggingFunction f,  Ts&& ... ts) {
		buffer_.start_write();

		bool good = write_to_buffer(buffer_, f);
		good = good && ((write_to_buffer(buffer_, ts)) && ...);
	
		if (good)
			buffer_.finish_write();
		else
			buffer_.cancel_write();

		return good;
	}

	bool try_read_log()  {
		buffer_.start_read();
		loggingFunction f;
		auto good = read_from_buffer(buffer_, f) && f(buffer_);
		if (!good)
			buffer_.cancel_read();
		else
			buffer_.finish_read();

		return good;
	}

	template <typename ... Ts>
	void log(loggingFunction f,  Ts&& ... ts) {
		// TODO(rHermes): Implement a max number of messages, that we can deduct based
		// on the capacity of the buffer and make sure the amount is not that. For now
		// we do a dummy of 100
		/* available_.wait(100, std::memory_order_acquire); */
		/* available_.wait(1, std::memory_order::acquire); */
		/* available_.wait(10); */
		available_.wait(10);

		/* std::cout << "we can log: " << available_.load() << std::endl; */

		bool good = try_log(f, ts...);
		if (!good)
				throw std::runtime_error("We were unable to write to the log, this should never happen");

		available_.fetch_add(1, std::memory_order::release);
		available_.notify_one();
	}
	
	// This can only be used with the log function pair, otherwise
	// this thread will never be woken up again.
	void read_log() {
		available_.wait(0, std::memory_order::acquire);

		bool good = try_read_log();
		if (!good)
				throw std::runtime_error("We were unable to read from read_log, this should never happen");

		available_.fetch_sub(1, std::memory_order::release);
		available_.notify_one();
	}
};

template <typename ... Ts, typename Buffer>
bool nullLogger(Buffer& buffer) {
	((read_from_buffer<Ts>(buffer)), ...);
	return true;
}

template <typename Buffer>
bool fooLogger(Buffer& buffer) {
	std::cout << "We called fooLogger with a=" 
		<< read_from_buffer<std::int64_t>(buffer)  
		<< " and b="
		<< read_from_buffer<std::string>(buffer) 
		<< '\n';

	return true;
}

/* #include <cassert> */

int main() {
	/* std::array<std::byte, 2097152> backing; */
	/* std::array<std::byte, 4096*2> backing; */
	/* SpanBuffer buf(backing, false); */

	/* Logger<QueueBuffer> logger; */
	/* Logger logger(std::move(buf)); */
	Logger<RingBuffer<4096>> logger;
	std::latch ready(2);

	constexpr std::int64_t TIMES = 10000;

	std::thread writer([&logger, &ready]() {
		ready.arrive_and_wait();
		std::string str("I hope this works!");
		std::int64_t i = 0;
		while (i < TIMES) {
			logger.log(nullLogger<std::int64_t, std::string>, i, str);
			i++;
		}

		logger.log(fooLogger, i, "The writer failed this many times.");
	});

	std::thread reader([&logger, &ready]() {
		ready.arrive_and_wait();
		std::int64_t i = 0;
		while (i < TIMES) {
			logger.read_log();
			i++;
		}

		logger.read_log();
	});

	writer.join();
	reader.join();

	return 0;
}
