/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_SINH_HPP
#define SPROUT_COMPLEX_SINH_HPP

#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/cosh.hpp>
#include <sprout/math/sinh.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/arithmetic_operators.hpp>
#include <sprout/complex/euler.hpp>
#include <sprout/complex/detail/copysign_mul.hpp>

namespace sprout {
	//
	// sinh
	//
	// G.6.2.5 The csinh functions
	// csinh(conj(z)) = conj(csinh(z)) and csinh is odd.
	// csinh(+0 + i0) returns +0 + i0.
	// csinh(+0 + i‡) returns }0 + iNaN (where the sign of the real part of the result is unspecified) and raises the eeinvalidff floating-point exception.
	// csinh(+0 + iNaN) returns }0 + iNaN (where the sign of the real part of the result is unspecified).
	// csinh(x + i‡) returns NaN + iNaN and raises the eeinvalidff floating-point exception, for positive finite x.
	// csinh(x + iNaN) returns NaN + iNaN and optionally raises the eeinvalidff floating-point exception, for finite nonzero x.
	// csinh(+‡+ i0) returns +‡+ i0.
	// csinh(+‡+ iy) returns +‡ cis(y), for positive finite y.
	// csinh(+‡+ i‡) returns }‡+ iNaN (where the sign of the real part of the result is unspecified) and raises the eeinvalidff floating-point exception.
	// csinh(+‡+ iNaN) returns }‡+ iNaN (where the sign of the real part of the result is unspecified).
	// csinh(NaN + i0) returns NaN + i0.
	// csinh(NaN + iy) returns NaN + iNaN and optionally raises the eeinvalidff floating-point exception, for all nonzero numbers y.
	// csinh(NaN + iNaN) returns NaN + iNaN.
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	sinh(sprout::complex<T> const& x) {
		typedef sprout::complex<T> type;
		return sprout::math::isnan(x.real())
				? sprout::math::isnan(x.imag()) ? type(x.real(), x.real())
				: sprout::math::isinf(x.imag()) ? type(x.real(), x.real())
				: x.imag() == 0 ? x
				: type(x.real(), x.real())
			: sprout::math::isnan(x.imag())
				? sprout::math::isinf(x.real()) ? type(x.real(), sprout::numeric_limits<T>::quiet_NaN())
				: x.real() == 0 ? type(x.real(), sprout::numeric_limits<T>::quiet_NaN())
				: type(x.imag(), x.imag())
			: x.real() == sprout::numeric_limits<T>::infinity()
				? sprout::math::isinf(x.imag()) ? type(x.real(), sprout::numeric_limits<T>::quiet_NaN())
				: x.imag() == 0 ? x
				: sprout::detail::copysign_mul(sprout::numeric_limits<T>::infinity(), sprout::euler(x.imag()))
			: x.real() == -sprout::numeric_limits<T>::infinity()
				? sprout::math::isinf(x.imag()) ? type(x.real(), sprout::numeric_limits<T>::quiet_NaN())
				: x.imag() == 0 ? x
				: -sprout::detail::copysign_mul(sprout::numeric_limits<T>::infinity(), sprout::euler(-x.imag()))
			: sprout::math::isinf(x.imag())
				? x.real() == 0 ? type(x.real(), sprout::numeric_limits<T>::quiet_NaN())
				: type(-sprout::numeric_limits<T>::quiet_NaN(), -sprout::numeric_limits<T>::quiet_NaN())
			: x.real() == 0 && x.imag() == 0 ? x
			: type(sprout::math::sinh(x.real()) * sprout::math::cos(x.imag()), sprout::math::cosh(x.real()) * sprout::math::sin(x.imag()))
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_SINH_HPP
