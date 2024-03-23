#include <array>
#include <cinttypes>
#include <cstring>
#include <deque>
#include <iostream>
#include <queue>
#include <span>
#include <format>
#include <mutex>
#include <atomic>
#include <thread>
#include <latch>

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

	std::atomic<std::ptrdiff_t> head_{0};
	std::ptrdiff_t cachedHead_{0};

	std::atomic<std::ptrdiff_t> tail_{0};
	std::ptrdiff_t cachedTail_{0};


	std::ptrdiff_t shadowHead_{0};
	std::ptrdiff_t shadowTail_{0};

	std::span<std::byte, N> buf_;

	[[nodiscard]]  constexpr std::size_t write_space_left() const {
		return buf_.size_bytes() - static_cast<std::size_t>(tail_);
	}

	[[nodiscard]]  constexpr std::size_t read_space_left() const {
		return static_cast<std::size_t>(tail_ - head_);
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
		if (cachedTail_ < shadowHead_ || (cachedTail_ - shadowHead_) < sz) {
			cachedTail_ = tail_.load(std::memory_order::acquire);

			if (cachedTail_ < shadowHead_ || (cachedTail_ - shadowHead_) < sz)
				return false;
		}

		std::memcpy(dst.data(), buf_.data() + shadowHead_, dst.size_bytes());
		shadowHead_ += dst.size_bytes();

		return true;
	}

	bool write(std::span<const std::byte> src) {
		const auto sz = static_cast<std::ptrdiff_t>(src.size_bytes());
		const auto bufSz = static_cast<std::ptrdiff_t>(buf_.size_bytes());

		if (shadowTail_ < cachedHead_ || (bufSz - shadowTail_) < sz) {
			cachedHead_ = head_.load(std::memory_order::acquire);

			if (shadowTail_ < cachedHead_ || (bufSz - shadowTail_) < sz)
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
		cachedTail_ = tail_.load(std::memory_order::acquire);
	}

	void finish_read() {
		// So, now we have either updated the head, or we haven't but we
		// store it anyway.
		head_.store(shadowHead_, std::memory_order::release);
	}

	void cancel_read() {}
	
	void start_write() {
		shadowTail_ = tail_.load(std::memory_order::relaxed);
		/* cachedHead_ = head_.load(std::memory_order::acquire); */

		// ok, so this is the special case. if we are start the write on
		// the same point as the reader, we can reset. We know that the
		// reader cannot have progressed past us.

		// this allows us to update the reader also.

		if (cachedHead_ == shadowTail_ && shadowTail_ != 0) {
			// First we store the tail behind.
			shadowTail_ = 0;
			cachedHead_ = 0;
			tail_.store(0, std::memory_order::release);
			head_.store(0, std::memory_order::release);
		}
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

template<typename BufferType>
struct Serializer<BufferType, std::string> {
	bool to_bytes(BufferType& buffer, const std::string& val) {
		bool good = true;
		good = good && write_to_buffer(buffer, val.size());
		good = good && buffer.write(std::as_bytes(std::span(val.begin(), val.end())));
		return good;
	};

	// TODO(rHermes): Decode what I want to do here. Should the value here be
	// accessable?
	bool from_bytes(BufferType& buffer, std::string& val) {
		std::string::size_type sz;
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
	
public:
	using loggingFunction = std::add_pointer_t<bool(Buffer&)>;

	Logger() {}
	Logger(Buffer buff) : buffer_{std::move(buff)} {}

	
	template <typename ... Ts>
	bool log(loggingFunction f,  Ts&& ... ts) {
		buffer_.start_write();

		bool good = write_to_buffer(buffer_, f);
		good = good && ((write_to_buffer(buffer_, ts)) && ...);
	
		if (good)
			buffer_.finish_write();
		else
			buffer_.cancel_write();

		return good;
	}

	bool read_log()  {
		buffer_.start_read();
		loggingFunction f;
		auto good = read_from_buffer(buffer_, f) && f(buffer_);
		if (!good)
			buffer_.cancel_read();
		else
			buffer_.finish_read();

		return good;
	}
};


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
	std::array<std::byte, 2048> backing;
	SpanBuffer buf(backing, false);

	/* Logger<QueueBuffer> logger; */
	Logger logger(std::move(buf));
	std::latch ready(2);

	constexpr std::int64_t TIMES = 10000;

	std::thread writer([&logger, &ready]() {
		ready.arrive_and_wait();
		std::string str("I hope this works!");
		std::int64_t i = 0;
		while (i < TIMES) {
			auto good = logger.log(fooLogger, i, str);
			if (good)
				i++;
		}
	});

	std::thread reader([&logger, &ready]() {
		ready.arrive_and_wait();
		std::int64_t i = 0;
		while (i < TIMES) {
			auto good = logger.read_log();
			if (good)
				i++;
		}
	});

	writer.join();
	reader.join();

	/* /1* assert(logger.log(fooLogger<QueueBuffer>, 23, std::string("I hope this works!"))); *1/ */
	/* /1* assert(logger.read_log()); *1/ */
	/* logger.log(fooLogger, 23, std::string("I hope this works!")); */
	/* logger.read_log(); */

	return 0;
}
