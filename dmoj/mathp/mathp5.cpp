/**
 * mathp5 - A Math Contest P5 - Good Arrays
 *
 * For each integer N, a good array is a non-empty array which satisfies the following conditions:
 * 
 *   Every element in the array is between the array's size and N, inclusive.
 *   The array is strictly increasing.
 *   There are no two consecutive integers in the array.
 *
 * Given an integer N, determine the number of good arrays. Output the answer modulo 10^9 + 7.
 *
 * This was such an interesting task, I learned so much from it! The way to solving this
 * was invovled and I will try to walk through all the stages I went through, to arrive at
 * current solution.
 *
 *
 * =============== STEP 1: Dynamic programming ==========================
 *
 * To begin with, this looked like a task that I could solve with some sort of dynamic
 * programming. Sure enough, I was able to find a way to break it down:
 *
 * S(n) = the number of good arrays for (N)
 *
 * Now S(n) is really the same as asking how many good arrays of length 1 there is,
 * how many of length 2, and so on. So we define a function F:
 *
 * F(n, d) = Number of arrays of length N, without subsequent items.
 *
 * ================= STEP 2: Finding a closed form for F(n, d) ============
 * 
 * ================ STEP 3: Realizing there is a recurrance equation ============
 *
 * ================ STEP 4: Figuring out why the closed form is correct ======
 *
 * ================ STEP 5: Converting recurrance to matrix form ===========
 *
 * ================ STEP 6: Exploring other optimizations ==================
 *
 * 
 *
 * https://math.stackexchange.com/a/4801204
 * https://oeis.org/wiki/Simplicial_polytopic_numbers#Formulae
 * https://en.wikipedia.org/wiki/Linear_recurrence_with_constant_coefficients#Conversion_to_homogeneous_form
 * https://en.wikipedia.org/wiki/Linear_recurrence_with_constant_coefficients
 *
 */
#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <numbers>
#include <unordered_map>
#include <vector>
#include <iostream>

using ST = std::int64_t;
using UT = std::uint64_t;

/* constexpr UT MAX_N = 10 * 10 * 10 * 10 * 10 * 10; */
constexpr UT MOD_M = 1000000007;

/* std::array<UT, MAX_N+1> factorial; */

template<typename T, std::size_t R, std::size_t C>
class Matrix {
	private:
		std::array<T, R*C> data_;

		static std::size_t getIndex(const std::size_t r, const std::size_t c) {
			return r*C + c;
		}

	public:
		
		Matrix() {
			data_.fill(0);
		}

		Matrix(const std::array<T, R*C>& dat) : data_{dat}{ }

		// Copy constructor
		Matrix(const Matrix& other) : data_{other.data_} { }
		// Move constructor
		Matrix(Matrix&& other) noexcept : data_{std::move(other.data_)} {}
	
		// Copy assignment
		Matrix& operator=(const Matrix& other) {
			data_ = other.data_;
			return *this;
		}

		// Move assigment
		Matrix& operator=(Matrix&& other) {
			if (this == &other)
				return *this;

			data_ = std::move(other.data_);
			return *this;
		}

		static Matrix Identity() {
			static_assert(R == C, "Only square matrixes have an identity");
			Matrix m;
			for (size_t i = 0; i < R; i++) {
				m.setCell(i, i, 1);
			}

			return m;
		}


		void setCell(const std::size_t r, const std::size_t c, const T val) {
			data_[getIndex(r, c)] = val;
		}

		[[nodiscard]] T getCell(const std::size_t r, const std::size_t c) const {
			return data_[getIndex(r, c)];
		}

		// TODO(rhermes): Add a constraint here thant R == C so we get a nice warning
		template<std::size_t K>
		Matrix<T, R, K> matrixMult(const Matrix<T, C, K>& rhs) {
			Matrix<T, R, K> m;
			
			for (std::size_t row = 0; row < R; row++) {
				for (std::size_t col = 0; col < K; col++) {
					T sum = 0;
					for (std::size_t k = 0; k < C; k++) {
						sum += getCell(row, k) * rhs.getCell(k, col);
					}

					m.setCell(row, col, sum);
				}
			}

			return m;
		}

		// TODO(rhermes): Add a constraint here thant R == C so we get a nice warning
		template<std::size_t K>
		Matrix<T, R, K> matrixMultMod(const Matrix<T, C, K>& rhs, const T modulus) {
			Matrix<T, R, K> m;
			
			for (std::size_t row = 0; row < R; row++) {
				for (std::size_t col = 0; col < K; col++) {
					T sum = 0;
					for (std::size_t k = 0; k < C; k++) {
						sum = (getCell(row, k) * rhs.getCell(k, col) + sum) % modulus;
					}

					m.setCell(row, col, sum);
				}
			}

			return m;
		}

		// TODO(rhermes): Add a constraint here thant R == C so we get a nice warning
		Matrix powerMod(std::size_t exponent, const T modulus) const {
			static_assert(R == C, "Only square matrixes can be taken the power of");
			Matrix base = *this % modulus;
			Matrix res = Matrix::Identity();

			while (0 < exponent) {
				if (exponent % 2 == 1)
					res = base.matrixMultMod(res, modulus);

				exponent >>= 1;
				base = base.matrixMultMod(base, modulus);
			}

			return res;
		}

		// Operators
		friend bool operator==(const Matrix& lhs, const Matrix& rhs) {
			return lhs.data_ == rhs.data_;
		}


		// === Matrix on matrix  ===

		Matrix& operator+=(const Matrix& rhs) {
			for (std::size_t i = 0; i < data_.size(); i++) {
				data_[i] += rhs.data_[i];
			}

			return *this;
		}

		friend Matrix operator+(Matrix lhs, const Matrix& rhs) {
			lhs += rhs;
			return lhs;
		}

		Matrix& operator-=(const Matrix& rhs) {
			for (std::size_t i = 0; i < data_.size(); i++) {
				data_[i] -= rhs.data_[i];
			}

			return *this;
		}

		friend Matrix operator-(Matrix lhs, const Matrix& rhs) {
			lhs -= rhs;
			return lhs;
		}

		// === Scalar on matrix ===
	
		Matrix& operator+=(const T rhs) {
			for (std::size_t i = 0; i < data_.size(); i++) {
				data_[i] += rhs;
			}
			return *this;
		}

		friend Matrix operator+(Matrix lhs, const T rhs) {
			lhs += rhs;
			return lhs;
		}

		Matrix& operator-=(const T rhs) {
			for (std::size_t i = 0; i < data_.size(); i++) {
				data_[i] -= rhs;
			}
			return *this;
		}

		friend Matrix operator-(Matrix lhs, const T rhs) {
			lhs -= rhs;
			return lhs;
		}

		Matrix& operator*=(const T rhs) {
			for (std::size_t i = 0; i < data_.size(); i++) {
				data_[i] *= rhs;
			}
			return *this;
		}

		friend Matrix operator*(Matrix lhs, const T rhs) {
			lhs *= rhs;
			return lhs;
		}

		Matrix& operator%=(const T rhs) {
			for (std::size_t i = 0; i < data_.size(); i++) {
				data_[i] %= rhs;
			}
			return *this;
		}

		friend Matrix operator%(Matrix lhs, const T rhs) {
			lhs %= rhs;
			return lhs;
		}

	
};

/* UT inverse(UT a) { */
/* 	if (a <= 1) { */
/* 		return a; */
/* 	} else { */
/* 		return MOD_M - static_cast<UT>(MOD_M/a) * inverse(MOD_M % a) % MOD_M; */
/* 	} */
/* } */

/* UT binomial_coefficient(UT n, UT k) { */
/* 	if (n < k) */
/* 		return 0; */

/* 	return factorial[n] * inverse(factorial[k] * factorial[n-k] % MOD_M) % MOD_M; */
/* } */

UT solve3(UT N) {
	if (N < 4)
		return N;


	UT t0 = 3; // t(n-0)
	UT t1 = 2; // t(n-1)
	UT t2 = 1; // t(n-2)
	
	for (UT i = 3; i < N; i++) {
		UT tn = (t0 + t2 + 1) % MOD_M;
		t2 = t1;
		t1 = t0;
		t0 = tn;
	}


	return t0;
}

UT solve2(UT N) {
	if (N < 4)
		return N;

	std::array<UT, 3*3> baseVals = {
		{1, 0, 1,
		1, 0, 0,
		0, 1, 0}
	};

	std::array<UT, 3> startVals = {
		{ 4, 3, 2},
	};

	Matrix<UT, 3, 3> base(baseVals);
	Matrix<UT, 3, 1> starts(startVals);

	auto lel = base.powerMod(N-3, MOD_M);

	/* printf("%lu %lu %lu\n", lel.getCell(0, 0), lel.getCell(0, 1), lel.getCell(0, 2)); */
	/* printf("%lu %lu %lu\n", lel.getCell(1, 0), lel.getCell(1, 1), lel.getCell(1, 2)); */
	/* printf("%lu %lu %lu\n", lel.getCell(2, 0), lel.getCell(2, 1), lel.getCell(2, 2)); */

	auto L = lel.matrixMultMod(starts, MOD_M);

	/* printf("%lu %lu %lu\n", L.getCell(0, 0), L.getCell(1, 0), L.getCell(2, 0)); */

	return L.getCell(0, 0) - 1;
}

/* UT solve(UT N) { */
/*   /1* printf("Called S(%lu)\n", N); *1/ */
/*   UT ans = 0; */
/* 	const UT maxN = (N + 1) / 2; */
/*   for (UT i = 1; i <= maxN; i++) { */
/* 		const UT left = N-i+1; */
/* 		const UT thisLen = binomial_coefficient(left - i + 1, i); */
/*     ans = (ans + thisLen) % MOD_M; */
/*   } */

/*   /1* printf("\n"); *1/ */
/*   return ans; */
/* } */

int main(void) {
	/* factorial[0] = 1; */
	/* for (UT i = 1; i <= MAX_N; i++) { */
	/* 	factorial[i] = (factorial[i-1] * i) % MOD_M; */
	/* } */
	

#ifdef ONLINE_JUDGE
  UT N;
  scanf("%lu", &N);
  printf("%lu\n", solve2(N));
#else
  std::vector<std::pair<UT, UT>> testCases = {
      /* {1, 1}, */
      /* {2, 2}, */
      /* {3, 3}, */
      /* {4, 5}, */
      /* {5, 8}, */
      /* {6, 12}, */
      /* {7, 18}, */
      /* {8, 27}, */
      /* {9, 40}, */
      /* {10, 59}, */
      /* {20, 2744}, */
      /* {30, 125490}, */
      /* {100, 332959340}, */
      /* {1000, 708863357}, */
      /* {10 * 10 * 10 * 2, 327988819}, */
      /* {10*10*10*10, 997127326}, */
      /* {10*10*10*10*10, 34605689}, */
      {10UL*10*10*10*10*10, 474866529},
      {10UL*10*10*10*10*10*10, 834496483},
      {10UL*10*10*10*10*10*10*10, 139745178},
      {10UL*10*10*10*10*10*10*10, 139745178},
  };

  for (const auto &[input, shouldBe] : testCases) {
    const auto start = std::chrono::high_resolution_clock::now();

    /* const auto ans = solve(input); */
    const auto ans = solve2(input);
    /* const auto ans = solve3(input); */

    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> diff = end - start;

    if (ans != shouldBe) {
      printf("Wrong answer for %lu, we calculated %lu, but it should be %lu\n", input, ans,
             shouldBe);
		} else {
			printf("S(%lu) took %.5f seconds to run\n", input, diff.count());
			/* std::cout << "Time to fill and iterate a vector of " << std::setw(9) << " ints : " << diff << '\n'; */
    }
  }
#endif

	return 0;
}
