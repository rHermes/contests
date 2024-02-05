#pragma once
#include <array>

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
			for (std::size_t i = 0; i < R; i++) {
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
