#include <cstdio>
#include <cstdint>

#include <algorithm>
#include <limits>
#include <string_view>
#include <vector>
#include <stdexcept>

class BigInt {
	private:
		using DT = std::uint64_t;

		bool negative_{false};
		std::vector<DT> digits_;

		void zero_out() {
				digits_.resize(1);
				digits_[0] = 0;
				negative_ = false;
		}

		// This is a pure add, without worring about scalar
		void pure_add(const DT rhs) {
				decltype(digits_)::size_type idx = 0;
				DT carry_in = rhs;

				while (0 < carry_in) {
					if (digits_.size() <= idx)
						digits_.push_back(0);

					carry_in = __builtin_add_overflow(digits_[idx], carry_in, &digits_[idx]); 
					idx++;
				}
		}

		// This is a pure add, without worring about the size
		void pure_add(const BigInt& rhs) {
			decltype(digits_)::size_type idx = 0;
			bool carry_in = false;

			do {
				if (digits_.size() <= idx)
					digits_.push_back(0);

				bool carry_out = __builtin_add_overflow(digits_[idx], carry_in, &digits_[idx]);

				if (idx < rhs.digits_.size())
					carry_out |= __builtin_add_overflow(digits_[idx], rhs.digits_[idx], &digits_[idx]);

				carry_in = carry_out;
				idx++;
			} while (carry_in || idx < rhs.digits_.size());
		}

		// This is a pure sub, without worrying about the sign. It' assumed here that the rhs is always smaller.
		void pure_sub(const BigInt& rhs) {
			if (digits_.size() < rhs.digits_.size())
				throw std::runtime_error("Pure sub called with a smaller lhs than rhs side");

			decltype(digits_)::size_type idx = 0;
			bool carry_in = false;

			do {
				if (digits_.size() <= idx)
					digits_.push_back(0);

				bool carry_out = __builtin_sub_overflow(digits_[idx], carry_in, &digits_[idx]);

				if (idx < rhs.digits_.size())
					carry_out |= __builtin_sub_overflow(digits_[idx], rhs.digits_[idx], &digits_[idx]);

				carry_in = carry_out;
				idx++;
			} while (carry_in || idx < rhs.digits_.size());

			normalize();
		}

		// Normalizes a number
		void normalize() {
			// now we just remove trailing zeros
			while (1 < digits_.size() && digits_.back() == 0)
				digits_.pop_back();

			if (is_zero())
				negative_ = false;
		}

		// Returns the quotient and remainder, not thinking about signs
		std::pair<BigInt,BigInt> pure_div(const BigInt& rhs) {
			BigInt one(1);
			BigInt Q;
			BigInt R = *this;

			while (!R.pure_less(rhs)) {
				Q.pure_add(one);
				R.pure_sub(rhs);
			}

			return {Q, R};
		}

		// Returns the quotient and remainder, not thinking about signs
		std::pair<BigInt,DT> pure_div(const DT& rhs) {
			// We use long division here.
			BigInt Q;

			DT leftover = 0;
			for (auto it = digits_.crbegin(); it != digits_.crend(); it++) {
				DT cur = *it;
				__uint128_t dividend = static_cast<__uint128_t>(leftover) << 64;
				dividend |= cur;

				__uint128_t qt = dividend / rhs;
				if (std::numeric_limits<DT>::max() < qt) {
					printf("Wtf this shouldn't happen\n");
				}
				leftover = dividend % rhs;
				Q.digits_.push_back(static_cast<DT>(qt));
			}

			// Now we just need to reverse the vector
			std::reverse(Q.digits_.begin(), Q.digits_.end());
			// If there is more than one digits, we remove the end.
			Q.normalize();

			return {Q, leftover};
		}
		
		bool pure_less(const BigInt& rhs) const {
			if (digits_.size() < rhs.digits_.size())
				return true;

			if (rhs.digits_.size() < digits_.size())
				return false;

			for (decltype(digits_)::size_type i = 0; i < digits_.size(); i++) {
				auto d = digits_.size() - 1 - i;
				if (digits_[d] < rhs.digits_[d])
					return true;

				if (digits_[d] > rhs.digits_[d])
					return false;
			}

			return false;
		}


	public:

		bool is_zero() const {
			return (digits_.size() == 1) && (digits_[0] == 0);
		}

		BigInt() : negative_{false} {
			digits_.push_back(0);
		}


		// BigInt + BigInt operator
		BigInt& operator+=(const BigInt& rhs) {
			if (rhs.is_zero())
				return *this;

			// ok, now we need to match up the signs.
			if (negative_ == rhs.negative_) {
				pure_add(rhs);
			} else {
				bool lhless = pure_less(rhs);
				if (lhless) {
					// we are less, so we need to swap
					BigInt tmp = *this;
					*this = rhs;

					pure_sub(tmp);
				} else {
					// we will be the bigger, so we don't have to deal with that.
					pure_sub(rhs);
				}

				// Due to not wanting 2 zeros, negative and positive,
				// we need to do a check here.
				if (is_zero())
					negative_ = false;
			}


			return *this;
		}

		friend BigInt operator+(BigInt lhs, const BigInt& rhs) {
			lhs += rhs;
			return lhs;
		}

		// BigInt - BigInt operator
		BigInt& operator-=(const BigInt& rhs) {
			if (rhs.is_zero())
				return *this;

			// ok, now we need to match up the signs.
			if (negative_ == rhs.negative_) {
				bool lhless = pure_less(rhs);
				if (lhless) {
					// we are less, so we need to swap
					BigInt tmp = *this;
					*this = rhs;

					pure_sub(tmp);
				} else {
					// we will be the bigger, so we don't have to deal with that.
					pure_sub(rhs);
				}

				// Due to not wanting 2 zeros, negative and positive,
				// we need to do a check here.
				if (is_zero())
					negative_ = false;

			} else {
				pure_add(rhs);
			}


			return *this;
		}

		friend BigInt operator-(BigInt lhs, const BigInt& rhs) {
			lhs -= rhs;
			return lhs;
		}

		BigInt& operator<<=(const DT& rhs) {
			if (is_zero())
				return *this;

			if (64 < rhs)
				throw std::runtime_error("to large of a shift");

			decltype(digits_)::size_type idx = 0;
			DT carry_in = 0;

			do {
				if (digits_.size() <= idx)
					digits_.push_back(0);

				DT carry_out = digits_[idx] >> (64 - rhs);

				digits_[idx] = (digits_[idx] << rhs) | carry_in;
				carry_in = carry_out;
				idx++;
			} while (carry_in || idx < digits_.size());

			normalize();


			return *this;
		}

		// smaller int multiplication
		BigInt& operator*=(const DT& rhs) {
			if (rhs == 0) {
				zero_out();

				return *this;
			}

			if (rhs == 1) {
				return *this;
			}

			if (rhs == 10) {
				BigInt tmp = *this;
				tmp <<= 1;
				*this <<= 3;
				*this += tmp;
				return *this;
			}

			/* printf("INCOMING: "); */
			/* print_digits(); */


			// WE use long hand multiplication
			BigInt res;
			for (DT i = 0; i < digits_.size(); i++) {
				__uint128_t mini = static_cast<__uint128_t>(rhs) * digits_[i];
				/* printf("%lu * %lu = ", rhs, digits_[i]); */

				BigInt tmp;
				tmp.digits_.clear();

				for (DT j = 0; j < i; j++) {
					tmp.digits_.push_back(0);
				}

				std::uint64_t base = static_cast<std::uint64_t>(mini);
				std::uint64_t carry = static_cast<std::uint64_t>(mini >> 64);
				tmp.digits_.push_back(base);
				tmp.digits_.push_back(carry);
				/* printf("%lu %lu\n", base, carry); */

				tmp.normalize();


				res += tmp;

			}

			/* res.print_digits(); */
			res.negative_ = negative_;

			// This is super slow, but it's what we are doing for now
			/* BigInt tmp = *this; */
			/* for (DT i = 0; i < rhs-1; i++) { */
			/* 	*this += tmp; */
			/* } */
			*this = res;

			/* printf("OUTGOING: "); */
			/* print_digits(); */


			return *this;
		}



		explicit BigInt(std::string_view decimal) : BigInt() {
			if (decimal.empty()) {
				throw std::invalid_argument("cannot parse empty number");
			}


			bool is_neg = false;
			if (decimal[0] == '-') {
				is_neg = true;
				decimal.remove_prefix(1);
			}

			for (auto it = decimal.cbegin(); it != decimal.cend(); it++) {
				if (*it < '0' || '9' < *it) {
					printf("We have a major problem, once character is outside: %c\n", *it);
				}

				uint8_t c = *it - '0';
				/* printf("%u\n", c); */

				BigInt w(c);

				*this *= 10;

				*this += w;
				/* print_digits(); */
			}

			negative_ = is_neg;

			normalize();
		}

		BigInt(int a) : BigInt() {
			if (a < 0) {
				negative_ = true;
				digits_[0] = -a;
			} else {
				negative_ = false;
				digits_[0] = a;
			}
		}


		// BigInt to BigInt relations
		friend bool operator<(const BigInt& lhs, const BigInt& rhs) {
			/* printf("We comparing lhs: [%lu], rhs: [%lu]\n", lhs.digits_[0], rhs.digits_[0]); */
			if (lhs.negative_) {
				if (rhs.negative_) {
					return rhs.pure_less(lhs);
				} else {
					return true;
				}
			} else {
				if (rhs.negative_) {
					return false;
				} else {
					return lhs.pure_less(rhs);
				}
			}
		}

		// The other relation operators
		friend bool operator>(const BigInt& lhs, const BigInt& rhs) { return rhs < lhs; }
		friend bool operator<=(const BigInt& lhs, const BigInt& rhs) { return !(lhs > rhs); }
		friend bool operator>=(const BigInt& lhs, const BigInt& rhs) { return !(lhs < rhs); }

		friend bool operator==(const BigInt& lhs, const BigInt& rhs) {
			return (lhs.negative_ == rhs.negative_) && (lhs.digits_ == rhs.digits_);
		}

		friend bool operator!=(const BigInt& lhs, const BigInt& rhs) {
			return !(lhs == rhs);
		}

		std::string to_decimal() const {
			if (is_zero())
				return "0";

			std::string res = "";
			BigInt W = *this;
			while (!W.is_zero()) {
				auto [Q, R] = W.pure_div(10);

				res = static_cast<char>('0' + R) + res;

				W = std::move(Q);
			}

			if (negative_)
				res = "-" + res;

			return res;
		}


		void print_digits() const {
			if (negative_)
				printf("NEGATIVE");
			else
				printf("POSITIVE");

			for (const auto& digit : digits_) {
				printf(" %lu", digit);
			}

			printf("\n");
		}

};

int main(void) {
	/* BigInt a, b; */

	/* a += 23; */
	/* b += 100; */

	/* printf("23 < 100: %d\n", a < b); */
	/* printf("23 > 100: %d\n", a > b); */

	/* BigInt c("1234"); */
	/* c.print_digits(); */
	int N;
	scanf("%d", &N);

	bool verbose = false;

	char buff[100000 + 100];
	for (int i = 0; i < N; i++) {
		scanf("%s", buff);
		BigInt a(buff);
		/* printf("We made it!\n"); */

		scanf("%s", buff);
		BigInt b(buff);

		/* printf("We made it!\n"); */
		auto c = a + b;
		printf("%s\n", c.to_decimal().c_str());

		if (verbose) {
			printf("====\n");
			a.print_digits();
			b.print_digits();
			c.print_digits();
			printf("====\n");
		}
		
	}

	return 0;
}
