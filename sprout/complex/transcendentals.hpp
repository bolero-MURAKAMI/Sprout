/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_TRANSCENDENTALS_HPP
#define SPROUT_COMPLEX_TRANSCENDENTALS_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/operators.hpp>
#include <sprout/complex/values.hpp>
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
	// 26.4.8, transcendentals:
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	acos(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	asin(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	atan(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	acosh(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	asinh(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	atanh(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	cos(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	cosh(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	exp(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	log(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	log10(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	pow(sprout::complex<T> const& x, T const& y);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	pow(sprout::complex<T> const& x, sprout::complex<T> const& y);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	pow(T const& x, sprout::complex<T> const& y);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	sin(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	sinh(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	sqrt(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	tan(sprout::complex<T> const& x);
	template<typename T>
	SPROUT_CONSTEXPR sprout::complex<T>
	tanh(sprout::complex<T> const& x);

	//
	// acos
	// asin
	// atan
	//
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		acos_impl(sprout::complex<T> const& t) {
			return sprout::complex<T>(sprout::math::half_pi<T>() - t.real(), -t.imag());
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	acos(sprout::complex<T> const& x) {
		return sprout::detail::acos_impl(sprout::asin(x));
	}
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		asin_impl(sprout::complex<T> const& t) {
			return sprout::complex<T>(t.imag(), -t.real());
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	asin(sprout::complex<T> const& x) {
		return sprout::detail::asin_impl(sprout::asinh(sprout::complex<T>(-x.imag(), x.real())));
	}
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		atan_impl_1(sprout::complex<T> const& x, T const& r2, T const& z, T const& num, T const& den) {
			return sprout::complex<T>(
				T(0.5) * sprout::atan2(T(2) * x.real(), z),
				T(0.25) * sprout::log((r2 + num * num) / (r2 + den * den))
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		atan_impl(sprout::complex<T> const& x, T const& r2) {
			return sprout::detail::atan_impl_1(
				x, r2,
				T(1) - r2 - x.imag() * x.imag(),
				x.imag() + T(1), x.imag() - T(1)
				);
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	atan(sprout::complex<T> const& x) {
		return sprout::detail::atan_impl(x, x.real() * x.real());
	}

	//
	// acosh
	// asinh
	// atanh
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	acosh(sprout::complex<T> const& x) {
		return T(2) * sprout::log(sprout::sqrt(T(0.5) * (x + T(1))) + sprout::sqrt(T(0.5) * (x - T(1))));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	asinh(sprout::complex<T> const& x) {
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
		inline SPROUT_CONSTEXPR sprout::complex<T>
		atanh_impl_1(sprout::complex<T> const& x, T const& i2, T const& z, T const& num, T const& den) {
			return sprout::complex<T>(
				T(0.25) * (sprout::log(i2 + num * num) - sprout::log(i2 + den * den)),
				T(0.5) * sprout::atan2(T(2) * x.imag(), z)
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		atanh_impl(sprout::complex<T> const& x, T const& i2) {
			return sprout::detail::atanh_impl_1(
				x, i2,
				T(1) - i2 - x.real() * x.real(),
				T(1) + x.imag(), T(1) - x.imag()
				);
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	atanh(sprout::complex<T> const& x) {
		return sprout::detail::atanh_impl(x, x.imag() * x.imag());
	}

	//
	// cos
	// cosh
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	cos(sprout::complex<T> const& x) {
		return sprout::complex<T>(
			sprout::cos(x.real()) * sprout::cosh(x.imag()),
			-(sprout::sin(x.real()) * sprout::sinh(x.imag()))
			);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	cosh(sprout::complex<T> const& x) {
		return sprout::complex<T>(
			sprout::cosh(x.real()) * sprout::cos(x.imag()),
			sprout::sinh(x.real()) * sprout::sin(x.imag())
			);
	}

	//
	// exp
	// log
	// log10
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	exp(sprout::complex<T> const& x) {
		return sprout::polar(sprout::exp(x.real()), x.imag());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	log(sprout::complex<T> const& x) {
		return sprout::complex<T>(sprout::log(sprout::abs(x)), sprout::arg(x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T> log10(sprout::complex<T> const& x) {
		return sprout::log(x) / sprout::log(T(10));
	}

	//
	// pow
	//
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T> pow_impl(sprout::complex<T> const& t, T const& y) {
			return sprout::polar(sprout::exp(y * t.real()), y * t.imag());
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	pow(sprout::complex<T> const& x, T const& y) {
		return x == T() ? T()
			: x.imag() == T() && x.real() > T() ? sprout::pow(x.real(), y)
			: sprout::detail::pow_impl(sprout::log(x), y)
			;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	pow(sprout::complex<T> const& x, sprout::complex<T> const& y) {
		return x == T() ? T()
			: sprout::exp(y * sprout::log(x))
			;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	pow(T const& x, sprout::complex<T> const& y) {
		return x > T() ? sprout::polar(sprout::pow(x, y.real()), y.imag() * sprout::log(x))
			: sprout::pow(sprout::complex<T>(x), y)
			;
	}

	//
	// sin
	// sinh
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	sin(sprout::complex<T> const& x) {
		return sprout::complex<T>(
			sprout::sin(x.real()) * sprout::cosh(x.imag()),
			sprout::cos(x.real()) * sprout::sinh(x.imag())
			);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	sinh(sprout::complex<T> const& x) {
		return sprout::complex<T>(
			sprout::sinh(x.real()) * sprout::cos(x.imag()),
			sprout::cosh(x.real()) * sprout::sin(x.imag())
			);
	}

	//
	// sqrt
	//
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		sqrt_impl_1(sprout::complex<T> const& x, T const& t) {
			return sprout::complex<T>(t, x.imag() < T() ? -t : t);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		sqrt_impl_2_1(sprout::complex<T> const& x, T const& t, T const& u) {
			return x.real() > T() ? sprout::complex<T>(u, x.imag() / t)
				: sprout::complex<T>(sprout::abs(x.imag()) / t, x.imag() < T() ? -u : u)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		sqrt_impl_2(sprout::complex<T> const& x, T const& t) {
			return sprout::detail::sqrt_impl_2_1(x, t, t / 2);
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	sqrt(sprout::complex<T> const& x) {
		return x.real() == T() ? sprout::detail::sqrt_impl_1(x, sprout::sqrt(abs(x.imag()) / 2))
			: sprout::detail::sqrt_impl_2(x, sprout::sqrt(2 * (sprout::abs(x) + sprout::abs(x.real()))))
			;
	}

	//
	// tan
	// tanh
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	tan(sprout::complex<T> const& x) {
		return sprout::sin(x) / sprout::cos(x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	tanh(sprout::complex<T> const& x) {
		return sprout::sinh(x) / sprout::cosh(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_TRANSCENDENTALS_HPP
