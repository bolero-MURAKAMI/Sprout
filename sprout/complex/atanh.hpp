/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_ATANH_HPP
#define SPROUT_COMPLEX_ATANH_HPP

#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/atan2.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/arithmetic_operators.hpp>
#include <sprout/complex/log.hpp>
#include <sprout/complex/sqrt.hpp>

namespace sprout {
	//
	// atanh
	//
	// G.6.2.3 The catanh functions
	// catanh(conj(z)) = conj(catanh(z)) and catanh is odd.
	// catanh(+0 + i0) returns +0 + i0.
	// catanh(+0 + iNaN) returns +0 + iNaN.
	// catanh(+1 + i0) returns +Åá+ i0 and raises the ÅeÅedivide-by-zeroÅfÅf floating-point exception.
	// catanh(x + iÅá) returns +0 + ip /2, for finite positive-signed x.
	// catanh(x + iNaN) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for nonzero finite x.
	// catanh(+Åá+ iy) returns +0 + ip /2, for finite positive-signed y.
	// catanh(+Åá+ iÅá) returns +0 + ip /2.
	// catanh(+Åá+ iNaN) returns +0 + iNaN.
	// catanh(NaN + iy) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for finite y.
	// catanh(NaN + iÅá) returns Å}0 + ip /2 (where the sign of the real part of the result is unspecified).
	// catanh(NaN + iNaN) returns NaN + iNaN.
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	atanh(sprout::complex<T> const& x) {
		typedef sprout::complex<T> type;
		return sprout::math::isnan(x.real())
				? sprout::math::isnan(x.imag()) ? type(x.imag(), x.imag())
				: sprout::math::isinf(x.imag()) ? type(sprout::math::copysign(T(0), x.real()), sprout::math::copysign(sprout::math::half_pi<T>(), x.imag()))
				: type(x.real(), x.real())
			: sprout::math::isnan(x.imag())
				? sprout::math::isinf(x.real()) ? type(sprout::math::copysign(T(0), x.real()), x.imag())
				: x.real() == 0 ? x
				: type(x.imag(), x.imag())
			: sprout::math::isinf(x.real()) || sprout::math::isinf(x.imag())
				? type(sprout::math::copysign(T(0), x.real()), sprout::math::copysign(sprout::math::half_pi<T>(), x.imag()))
			: x.real() == 0 && x.imag() == 0 ? x
			: (x.real() == 1 || x.real() == -1) && x.imag() == 0 ? type(sprout::math::copysign(sprout::numeric_limits<T>::infinity(), x.real()), x.imag())
			: (sprout::log(T(1) + x) - sprout::log(T(1) - x)) / T(2)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_ATANH_HPP
