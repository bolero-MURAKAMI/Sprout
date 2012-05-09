#ifndef SPROUT_COMPLEX_HPP
#define SPROUT_COMPLEX_HPP

#include <iosfwd>
#include <ios>
#include <sprout/config.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/abs.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/atan2.hpp>
#include <sprout/math/sinh.hpp>
#include <sprout/math/cosh.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/pow.hpp>
#include <sprout/math/sqrt.hpp>

namespace sprout {
	template<typename T>
	class complex;
	template<typename T>
	SPROUT_CONSTEXPR T norm(sprout::complex<T> const& x);
	//
	// complex
	//
	template<typename T>
	class complex {
	public:
		typedef T value_type;
	private:
		T re_;
		T im_;
	public:
		SPROUT_CONSTEXPR complex(T const& re = T(), T const& im = T())
			: re_(re)
			, im_(im)
		{}
		SPROUT_CONSTEXPR complex(complex const&) = default;
		template<typename X>
		SPROUT_CONSTEXPR complex(complex<X> const& other)
			: re_(other.real())
			, im_(other.imag())
		{}
		SPROUT_CONSTEXPR T real() const {
			return re_;
		}
		void real(T re) {
			re_ = re;
		}
		SPROUT_CONSTEXPR T imag() const{
			return im_;
		}
		void imag(T im) {
			im_ = im;
		}
		complex<T>& operator=(T const& rhs) {
			re_ = rhs;
			im_ = T();
			return *this;
		}
		complex<T>& operator+=(T const& rhs) {
			re_ += rhs;
			return *this;
		}
		complex<T>& operator-=(T const& rhs) {
			re_ -= rhs;
			return *this;
		}
		complex<T>& operator*=(T const& rhs) {
			re_ *= rhs;
			im_ *= rhs;
			return *this;
		}
		complex<T>& operator/=(T const& rhs) {
			re_ /= rhs;
			im_ /= rhs;
			return *this;
		}
		complex& operator=(complex const&) = default;
		template<typename X>
		complex<T>& operator=(complex<X> const& rhs) {
			re_ = rhs.real();
			im_ = rhs.imag();
			return *this;
		}
		template<typename X>
		complex<T>& operator+=(complex<X> const& rhs) {
			re_ += rhs.real();
			im_ += rhs.imag();
			return *this;
		}
		template<typename X>
		complex<T>& operator-=(complex<X> const& rhs) {
			re_ -= rhs.real();
			im_ -= rhs.imag();
			return *this;
		}
		template<typename X>
		complex<T>& operator*=(complex<X> const& rhs) {
			return *this = complex<T>(
				re_ * rhs.real() - im_ * rhs.imag(),
				re_ * rhs.imag() + im_ * rhs.real()
				);
		}
		template<typename X>
		complex<T>& operator/=(complex<X> const& rhs) {
			T n = sprout::norm(rhs);
			return *this = complex<T>(
				(re_ * rhs.real() + im_ * rhs.imag()) / n,
				(im_ * rhs.real() - re_ * rhs.imag()) / n
				);
		}
	};
	// 26.4.6, operators:
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator+(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(
			lhs.real() + rhs.real(),
			lhs.imag() + rhs.imag()
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator+(sprout::complex<T> const& lhs, T const& rhs) {
		return sprout::complex<T>(
			lhs.real() + rhs,
			lhs.imag()
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator+(T const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(
			lhs + rhs.real(),
			rhs.imag()
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator-(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(
			lhs.real() - rhs.real(),
			lhs.imag() - rhs.imag()
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator-(sprout::complex<T> const& lhs, T const& rhs) {
		return sprout::complex<T>(
			lhs.real() - rhs,
			lhs.imag()
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator-(T const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(
			lhs - rhs.real(),
			-rhs.imag()
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator*(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(
			lhs.real() * rhs.real() - lhs.imag() * rhs.imag(),
			lhs.real() * rhs.imag() + lhs.imag() * rhs.real()
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator*(sprout::complex<T> const& lhs, T const& rhs) {
		return sprout::complex<T>(
			lhs.real() * rhs,
			lhs.imag() * rhs
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator*(T const& lhs, sprout::complex<T> const& rhs) {
		return sprout::complex<T>(
			lhs * rhs.real(),
			lhs * rhs.imag()
			);
	}
	namespace detail {
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> divides_impl(
			sprout::complex<T> const& lhs,
			sprout::complex<T> const& rhs,
			T const& n
			)
		{
			return sprout::complex<T>(
				(lhs.real() * rhs.real() + lhs.imag() * rhs.imag()) / n,
				(lhs.imag() * rhs.real() - lhs.real() * rhs.imag()) / n
				);
		}
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> divides_impl(
			T const& lhs,
			sprout::complex<T> const& rhs,
			T const& n
			)
		{
			return sprout::complex<T>(
				lhs * rhs.real() / n,
				-lhs * rhs.imag() / n
				);
		}
	}	// namespace detail
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator/(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return sprout::detail::divides_impl(lhs, rhs, sprout::norm(rhs));
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator/(sprout::complex<T> const& lhs, T const& rhs) {
		return sprout::complex<T>(
			lhs.real() / rhs,
			lhs.imag() / rhs
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator/(T const& lhs, sprout::complex<T> const& rhs) {
		return sprout::detail::divides_impl(lhs, rhs, sprout::norm(rhs));
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator+(sprout::complex<T> const& x) {
		return x;
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> operator-(sprout::complex<T> const& x) {
		return sprout::complex<T>(-x.real(), -x.imag());
	}
	template<typename T>
	SPROUT_CONSTEXPR bool operator==(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
	}
	template<typename T>
	SPROUT_CONSTEXPR bool operator==(sprout::complex<T> const& lhs, T const& rhs) {
		return lhs.real() == rhs && lhs.imag() == T();
	}
	template<typename T>
	SPROUT_CONSTEXPR bool operator==(T const& lhs, sprout::complex<T> const& rhs) {
		return lhs == rhs.real() && T() == rhs.imag();
	}
	template<typename T>
	SPROUT_CONSTEXPR bool operator!=(sprout::complex<T> const& lhs, sprout::complex<T> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T>
	SPROUT_CONSTEXPR bool operator!=(sprout::complex<T> const& lhs, T const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T>
	SPROUT_CONSTEXPR bool operator!=(T const& lhs, sprout::complex<T> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, typename Char, typename Traits>
	std::basic_istream<Char, Traits>& operator>>(std::basic_istream<Char, Traits>& lhs, sprout::complex<T>& rhs) {
		T re, im;
		Char ch;
		lhs >> ch;
		if (ch == '(') {
			lhs >> re >> ch;
			if (ch == ',') {
				lhs >> im >> ch;
				if (ch == ')') {
					rhs = sprout::complex<T>(re, im);
				} else {
					lhs.setstate(std::ios_base::failbit);
				}
			} else if (ch == ')') {
				rhs = re;
			} else {
				lhs.setstate(std::ios_base::failbit);
			}
		} else {
			lhs.putback(ch);
			lhs >> re;
			rhs = re;
		}
		return lhs;
	}
	template<typename T, typename Char, typename Traits>
	std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& lhs, sprout::complex<T> const& rhs) {
		return lhs << '(' << rhs.real() << ',' << rhs.imag() << ')';
	}
	// 26.4.7, values:
	template<typename T>
	SPROUT_CONSTEXPR T real(sprout::complex<T> const& x) {
		return x.real();
	}
	template<typename T>
	SPROUT_CONSTEXPR T imag(sprout::complex<T> const& x) {
		return x.imag();
	}
	template<typename T>
	SPROUT_CONSTEXPR T abs(sprout::complex<T> const& x) {
		using sprout::sqrt;
		return sqrt(sprout::norm(x));
	}
	template<typename T>
	SPROUT_CONSTEXPR T arg(sprout::complex<T> const& x) {
		using sprout::atan2;
		return atan2(x.imag(), x.real());
	}
	template<typename T>
	SPROUT_CONSTEXPR T norm(sprout::complex<T> const& x) {
		return x.real() * x.real() + x.imag() * x.imag();
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> conj(sprout::complex<T> const& x) {
		return sprout::complex<T>(x.real(), -x.imag());
	}
	namespace detail {
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> proj_impl(sprout::complex<T> const& x, T const& den) {
			return sprout::complex<T>(
				T(2) * x.real() / den,
				T(2) * x.imag() / den
				);
		}
	}	// detail
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> proj(sprout::complex<T> const& x) {
		return sprout::detail::proj_impl(
			x,
			sprout::norm(x) + T(1)
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> polar(T const& rho, T const& theta = 0) {
		using sprout::cos;
		using sprout::sin;
		return sprout::complex<T>(rho * cos(theta), rho * sin(theta));
	}
	// 26.4.8, transcendentals:
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> acos(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> asin(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> atan(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> acosh(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> asinh(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> atanh(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> cos(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> cosh(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> exp(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> log(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> log10(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> pow(sprout::complex<T> const& x, T const& y);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> pow(sprout::complex<T> const& x, sprout::complex<T> const& y);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> pow(T const& x, sprout::complex<T> const& y);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> sin(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> sinh(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> sqrt(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> tan(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> tanh(sprout::complex<T> const& x);
	namespace detail {
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> acos_impl(sprout::complex<T> const& t) {
			return sprout::complex<T>(sprout::math::half_pi<T>() - t.real(), -t.imag());
		}
	}	// namespace detail
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> acos(sprout::complex<T> const& x) {
		return sprout::detail::acos_impl(sprout::asin(x));
	}
	namespace detail {
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> asin_impl(sprout::complex<T> const& t) {
			return sprout::complex<T>(t.imag(), -t.real());
		}
	}	// namespace detail
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> asin(sprout::complex<T> const& x) {
		return sprout::detail::asin_impl(sprout::asinh(sprout::complex<T>(-x.imag(), x.real())));
	}
	namespace detail {
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> atan_impl_1(
			sprout::complex<T> const& x,
			T const& r2,
			T const& z,
			T const& num,
			T const& den
			)
		{
			using sprout::atan2;
			using sprout::log;
			return sprout::complex<T>(
				T(0.5) * atan2(T(2) * x.real(), z),
				T(0.25) * log((r2 + num * num) / (r2 + den * den))
				);
		}
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> atan_impl(
			sprout::complex<T> const& x,
			T const& r2
			)
		{
			return sprout::detail::atan_impl_1(
				x,
				r2,
				T(1) - r2 - x.imag() * x.imag(),
				x.imag() + T(1),
				x.imag() - T(1)
				);
		}
	}	// namespace detail
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> atan(sprout::complex<T> const& x) {
		return sprout::detail::atan_impl(x, x.real() * x.real());
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> acosh(sprout::complex<T> const& x) {
		return T(2) * sprout::log(sprout::sqrt(T(0.5) * (x + T(1))) + sprout::sqrt(T(0.5) * (x - T(1))));
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> asinh(sprout::complex<T> const& x) {
		return sprout::log(
			sprout::sqrt(
				sprout::complex<T>(
					(x.real() - x.imag()) * (x.real() + x.imag()) + T(1),
					T(2) * x.real() * x.imag()
					)
				)
				+ x
			);
	}
	namespace detail {
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> atanh_impl_1(
			sprout::complex<T> const& x,
			T const& i2,
			T const& z,
			T const& num,
			T const& den
			)
		{
			using sprout::atan2;
			using sprout::log;
			return sprout::complex<T>(
				T(0.25) * (log(i2 + num * num) - log(i2 + den * den)),
				T(0.5) * atan2(T(2) * x.imag(), z)
				);
		}
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> atanh_impl(
			sprout::complex<T> const& x,
			T const& i2
			)
		{
			return sprout::detail::atanh_impl_1(
				x,
				i2,
				T(1) - i2 - x.real() * x.real(),
				T(1) + x.imag(),
				T(1) - x.imag()
				);
		}
	}	// namespace detail
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> atanh(sprout::complex<T> const& x) {
		return sprout::detail::atanh_impl(x, x.imag() * x.imag());
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> cos(sprout::complex<T> const& x) {
		using sprout::cos;
		using sprout::sin;
		using sprout::cosh;
		using sprout::sinh;
		return sprout::complex<T>(
			cos(x.real()) * cosh(x.imag()),
			-(sin(x.real()) * sinh(x.imag()))
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> cosh(sprout::complex<T> const& x) {
		using sprout::cos;
		using sprout::sin;
		using sprout::cosh;
		using sprout::sinh;
		return sprout::complex<T>(
			cosh(x.real()) * cos(x.imag()),
			sinh(x.real()) * sin(x.imag())
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> exp(sprout::complex<T> const& x) {
		using sprout::exp;
		return sprout::polar(exp(x.real()), x.imag());
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> log(sprout::complex<T> const& x) {
		return sprout::complex<T>(sprout::log(sprout::abs(x)), sprout::arg(x));
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> log10(sprout::complex<T> const& x) {
		using sprout::log;
		return sprout::log(x) / log(T(10));
	}
	namespace detail {
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> pow_impl(sprout::complex<T> const& t, T const& y) {
			using sprout::exp;
			return sprout::polar(exp(y * t.real()), y * t.imag());
		}
	}	// namespace detail
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> pow(sprout::complex<T> const& x, T const& y) {
		using sprout::pow;
		return x == T() ? T()
			: x.imag() == T() && x.real() > T() ? pow(x.real(), y)
			: sprout::detail::pow_impl(sprout::log(x), y)
			;
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> pow(sprout::complex<T> const& x, sprout::complex<T> const& y) {
		return x == T() ? T()
			: sprout::exp(y * sprout::log(x))
			;
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> pow(T const& x, sprout::complex<T> const& y) {
		using sprout::log;
		return x > T() ? sprout::polar(sprout::pow(x, y.real()), y.imag() * log(x))
			: sprout::pow(sprout::complex<T>(x), y)
			;
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> sin(sprout::complex<T> const& x) {
		using sprout::cos;
		using sprout::sin;
		using sprout::cosh;
		using sprout::sinh;
		return sprout::complex<T>(
			sin(x.real()) * cosh(x.imag()),
			cos(x.real()) * sinh(x.imag())
			);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> sinh(sprout::complex<T> const& x) {
		using sprout::cos;
		using sprout::sin;
		using sprout::cosh;
		using sprout::sinh;
		return sprout::complex<T>(
			sinh(x.real()) * cos(x.imag()),
			cosh(x.real()) * sin(x.imag())
			);
	}
	namespace detail {
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> sqrt_impl_1(sprout::complex<T> const& x, T const& t) {
			return sprout::complex<T>(t, x.imag() < T() ? -t : t);
		}
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> sqrt_impl_2_1(sprout::complex<T> const& x, T const& t, T const& u) {
			using sprout::abs;
			return x.real() > T() ? sprout::complex<T>(u, x.imag() / t)
				: sprout::complex<T>(abs(x.imag()) / t, x.imag() < T() ? -u : u)
				;
		}
		template<typename T>
		SPROUT_CONSTEXPR sprout::complex<T> sqrt_impl_2(sprout::complex<T> const& x, T const& t) {
			return sqrt_impl_2(x, t, t / 2);
		}
	}	// namespace detail
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> sqrt(sprout::complex<T> const& x) {
		using sprout::sqrt;
		using sprout::abs;
		return x.real() == T() ? sprout::detail::sqrt_impl_1(x, sqrt(abs(x.imag()) / 2))
			: sprout::detail::sqrt_impl_2(x, sqrt(2 * (sprout::abs(x) + abs(x.real()))))
			;
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> tan(sprout::complex<T> const& x) {
		return sprout::sin(x) / sprout::cos(x);
	}
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T> tanh(sprout::complex<T> const& x) {
		return sprout::sinh(x) / sprout::cosh(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_HPP
