/**
 * aplusb2 - A Plus B (Hard)
 *
 * This task is about adding together big numbers. I tried to first implement
 * this with a proper BigInt implementation, which was in base 2^64, but what
 * takes up most of the time then is converting to and from base 10 to that
 * base.
 *
 * So instead I dumbed it down and implemented it in base 10. Since the
 * only operation needed is plus, we can get away with this. It's not the
 * fastest solution, but I think that when stacked up against some of the
 * faster ones on the leader board, it actually comes out pretty well.
 *
 * You can find the older implementation in "aplusb2-large-base.cpp".
 */
#include <cstdio>
#include <cstdint>

#include <algorithm>
#include <string_view>
#include <vector>
#include <stdexcept>

class SmolInt {
	private:
		bool negative_{false};
		std::vector<std::uint8_t> digits_;


		void normalize() {
			if (digits_.empty())
				digits_.push_back(0);

			while (1 < digits_.size() && digits_.back() == 0)
				digits_.pop_back();

			if (is_zero())
				negative_ = false;
		}

		// Just add the numbers together, don't care about anything else.
		void pure_add(const SmolInt& rhs) {
			decltype(digits_)::size_type idx = 0;
			bool carry_in = false;

			do {
				if (digits_.size() <= idx)
					digits_.push_back(0);

				std::uint8_t ss = carry_in + digits_[idx];
				if (idx < rhs.digits_.size())
					ss += rhs.digits_[idx];

				digits_[idx] = ss % 10;
				carry_in = ss >= 10;

				idx++;
			} while (carry_in || idx < rhs.digits_.size());
		}

		// Just subtract the numbers. Rhs must be strictly smaller than
		// lhs.
		void pure_sub(const SmolInt& rhs) {
			decltype(digits_)::size_type idx = 0;
			bool carry_in = false;

			do {
				std::uint8_t ss = carry_in;
				if (idx < rhs.digits_.size())
					ss += rhs.digits_[idx];

				if (digits_[idx] < ss) {
					carry_in = true;
					digits_[idx] = static_cast<std::uint8_t>(digits_[idx] + 10 - ss);
				} else {
					carry_in = false;
					digits_[idx] = digits_[idx] - ss;
				}

				idx++;
			} while (carry_in || idx < rhs.digits_.size());
		}

		bool pure_less(const SmolInt& rhs) {
			const auto lsz = digits_.size();
			const auto rsz = rhs.digits_.size();

			if (lsz < rsz)
				return true;
			
			if (rsz < lsz)
				return false;

			return std::lexicographical_compare(digits_.crbegin(), digits_.crend(),
					rhs.digits_.crbegin(), rhs.digits_.crend());
		}


	public:

		SmolInt& operator+=(const SmolInt& rhs) {
			// We check to see if they have the same prefix
			if (negative_ == rhs.negative_) {
				// We have a pure add situation.
				pure_add(rhs);
			} else {
				// We are going to have a negative situation. We figure out which is smaller.
				if (pure_less(rhs)) {
					SmolInt tmp = *this;
					*this = rhs;
					pure_sub(tmp);
				} else {
					pure_sub(rhs);
				}
			}

			normalize();

			return *this;
		}

		friend SmolInt operator+(SmolInt lhs, const SmolInt& rhs) {
			lhs += rhs;
			return lhs;
		}

		bool is_zero() const {
			return digits_.size() == 1 && digits_.front() == 0;
		}

		SmolInt() {
			digits_.push_back(0);
		}

		SmolInt(std::string_view input) : SmolInt() {
			if (input.empty())
				throw std::runtime_error("Empty input to smolint");

			if (input.front() == '-') {
				negative_ = true;
				input.remove_prefix(1);
			}

			digits_.clear();
			for (auto it = input.crbegin(); it != input.crend(); it++) {
				if (*it < '0' || '9' < *it)
					throw std::runtime_error("invalid numeric input!");

				std::uint8_t c = static_cast<std::uint8_t>(*it - '0');
				digits_.push_back(c);
			}

			normalize();
		}

		std::string to_decimal() const {
			std::string ret;

			if (negative_)
				ret = "-" + ret;

			for (auto it = digits_.crbegin(); it != digits_.crend(); it++)
				ret += static_cast<char>('0' + *it);


			return ret;
		}
};

int main(void) {
	int N;
	scanf("%d", &N);

	char buff[100000 + 100];
	for (int i = 0; i < N; i++) {
		scanf("%s", buff);
		SmolInt a(buff);

		scanf("%s", buff);
		SmolInt b(buff);

		a += b;
		printf("%s\n", a.to_decimal().c_str());
	}

	return 0;
}
