#pragma once

#include <numeric>
#include <stdexcept>

template <typename T>
class Fraction {
	private:
		T nom_{0};
		T den_{1};

		void reduce() {
			if (den_ == 0)
				throw std::domain_error("Denominator is 0");

			const auto d = std::gcd(nom_, den_);
			nom_ /= d;
			den_ /= d;

			// We always want the negative in the numerator.
			if (den_ < 0) {
				nom_ = -nom_;
				den_ = -den_;
			}
		}

	public:
		Fraction() {}

		Fraction(T n, T d) : nom_{n}, den_{d} {
			this->reduce();
		}

		Fraction(T n) : nom_{n}, den_{1} {}

		[[nodiscard]] T nom() const {
			return nom_;
		}
		[[nodiscard]] T den() const {
			return den_;
		}

		[[nodiscard]] bool isZero() const {
			return nom_ == 0;
		}
	
		// Operators
		Fraction& operator+=(const Fraction& rhs) {
			const auto common = std::lcm(this->den_, rhs.den_);
			const auto lhsScale = common / this->den_;
			const auto rhsScale = common / rhs.den_;

			this->nom_ = this->nom_*lhsScale + rhs.nom_*rhsScale;
			this->den_ = common;

			this->reduce();

			return *this;
		}

		friend Fraction operator+(Fraction lhs, const Fraction& rhs) {
			lhs += rhs;
			return lhs;
		}

		Fraction& operator-=(const Fraction& rhs) {
			const auto common = std::lcm(this->den_, rhs.den_);
			const auto lhsScale = common / this->den_;
			const auto rhsScale = common / rhs.den_;

			this->nom_ = this->nom_*lhsScale - rhs.nom_*rhsScale;
			this->den_ = common;

			this->reduce();
			return *this;
		}

		friend Fraction operator-(Fraction lhs, const Fraction& rhs) {
			lhs -= rhs;
			return lhs;
		}

		Fraction& operator*=(const Fraction& rhs) {
			this->nom_ *= rhs.nom_;
			this->den_ *= rhs.den_;

			this->reduce();
			return *this;
		}

		friend Fraction operator*(Fraction lhs, const Fraction& rhs) {
			lhs *= rhs;
			return lhs;
		}

		Fraction& operator/=(const Fraction& rhs) {
			this->nom_ *= rhs.den_;
			this->den_ *= rhs.nom_;

			this->reduce();
			return *this;
		}

		friend Fraction operator/(Fraction lhs, const Fraction& rhs) {
			lhs /= rhs;
			return lhs;
		}
};
