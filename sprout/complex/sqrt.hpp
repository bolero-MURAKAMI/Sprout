/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_SQRT_HPP
#define SPROUT_COMPLEX_SQRT_HPP

#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/abs.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/abs.hpp>

namespace sprout {
	//
	// sqrt
	//
	// G.6.4.2 The csqrt functions
	// csqrt(conj(z)) = conj(csqrt(z)).
	// csqrt(Å}0 + i0) returns +0 + i0.
	// csqrt(x + iÅá) returns +Åá+ iÅá, for all x (including NaN).
	// csqrt(x + iNaN) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for finite x.
	// csqrt(-Åá+ iy) returns +0 + iÅá, for finite positive-signed y.
	// csqrt(+Åá+ iy) returns +Åá+ i0, for finite positive-signed y.
	// csqrt(-Åá+ iNaN) returns NaN Å} iÅá (where the sign of the imaginary part of the result is unspecified).
	// csqrt(+Åá+ iNaN) returns +Åá+ iNaN.
	// csqrt(NaN + iy) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for finite y.
	// csqrt(NaN + iNaN) returns NaN + iNaN.
	//
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		sqrt_impl_1(sprout::complex<T> const& x, T const& t) {
			return sprout::complex<T>(t, sprout::math::signbit(x.imag()) ? -t : t);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		sqrt_impl_2_1(sprout::complex<T> const& x, T const& t, T const& u) {
			return x.real() > T(0) ? sprout::complex<T>(u, x.imag() / t)
				: sprout::complex<T>(sprout::math::abs(x.imag()) / t, sprout::math::signbit(x.imag()) ? -u : u)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		sqrt_impl_2(sprout::complex<T> const& x, T const& t) {
			return sprout::detail::sqrt_impl_2_1(x, t, t / T(2));
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	sqrt(sprout::complex<T> const& x) {
		typedef sprout::complex<T> type;
		return sprout::math::isinf(x.imag()) ? type(sprout::numeric_limits<T>::infinity(), x.imag())
			: sprout::math::isnan(x.real())
				? sprout::math::isnan(x.imag()) ? type(sprout::numeric_limits<T>::quiet_NaN(), sprout::numeric_limits<T>::quiet_NaN())
				: type(sprout::numeric_limits<T>::quiet_NaN(), sprout::numeric_limits<T>::quiet_NaN())
			: sprout::math::isnan(x.imag())
				? x.real() == sprout::numeric_limits<T>::infinity()
					? type(sprout::numeric_limits<T>::infinity(), sprout::math::copysign(sprout::numeric_limits<T>::quiet_NaN(), x.imag()))
				: x.real() == -sprout::numeric_limits<T>::infinity()
					? type(
						sprout::math::copysign(sprout::numeric_limits<T>::quiet_NaN(), x.imag()),
						sprout::math::copysign(sprout::numeric_limits<T>::infinity(), x.imag())
						)
				: type(sprout::numeric_limits<T>::quiet_NaN(), sprout::numeric_limits<T>::quiet_NaN())
			: x.real() == sprout::numeric_limits<T>::infinity()
				? type(sprout::numeric_limits<T>::infinity(), (x.imag() == 0 ? x.imag() : sprout::math::copysign(T(0), x.imag())))
			: x.real() == -sprout::numeric_limits<T>::infinity()
				? type(T(0), sprout::math::copysign(T(0), x.imag()))
			: x.real() == 0 && x.imag() == 0 ? type(T(0), x.imag())
			: x.real() == 0 ? sprout::detail::sqrt_impl_1(x, sprout::math::sqrt(sprout::math::abs(x.imag()) / T(2)))
			: sprout::detail::sqrt_impl_2(x, sprout::math::sqrt(T(2) * (sprout::abs(x) + sprout::math::abs(x.real()))))
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_SQRT_HPP
