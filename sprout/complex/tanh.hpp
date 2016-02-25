/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_TANH_HPP
#define SPROUT_COMPLEX_TANH_HPP

#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/operators.hpp>
#include <sprout/complex/cosh.hpp>
#include <sprout/complex/sinh.hpp>

namespace sprout {
	//
	// tanh
	//
	// G.6.2.6 The ctanh functions
	// ctanh(conj(z)) = conj(ctanh(z))and ctanh is odd.
	// ctanh(+0 + i0) returns +0 + i0.
	// ctanh(x + iÅá) returns NaN + iNaN and raises the ÅeÅeinvalidÅfÅf floating-point exception, for finite x.
	// ctanh(x + iNaN) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for finite x.
	// ctanh(+Åá+ iy) returns 1 + i0 sin(2y), for positive-signed finite y.
	// ctanh(+Åá+ iÅá) returns 1 Å} i0 (where the sign of the imaginary part of the result is unspecified).
	// ctanh(+Åá+ iNaN) returns 1 Å} i0 (where the sign of the imaginary part of the result is unspecified).
	// ctanh(NaN + i0) returns NaN + i0.
	// ctanh(NaN + iy) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for all nonzero numbers y.
	// ctanh(NaN + iNaN) returns NaN + iNaN.
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	tanh(sprout::complex<T> const& x) {
		typedef sprout::complex<T> type;
		return sprout::math::isnan(x.real())
				? sprout::math::isnan(x.imag()) ? x
				: x.imag() == 0 ? x
				: type(x.real(), x.real())
			: sprout::math::isnan(x.imag())
				? sprout::math::isinf(x.real()) ? type(T(1), T(0))
				: type(x.imag(), x.imag())
			: sprout::math::isinf(x.real())
				? sprout::math::isinf(x.imag()) ? type(T(1), T(0))
				: type(T(1), T(0) * sprout::math::sin(T(2) * x.imag()))
			: sprout::math::isinf(x.imag())
				? type(-sprout::numeric_limits<T>::quiet_NaN(), -sprout::numeric_limits<T>::quiet_NaN())
			: x.real() == 0 && x.imag() == 0 ? x
			: sprout::sinh(x) / sprout::cosh(x)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_TANH_HPP
