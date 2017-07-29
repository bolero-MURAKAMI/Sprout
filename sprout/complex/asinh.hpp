/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_ASINH_HPP
#define SPROUT_COMPLEX_ASINH_HPP

#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/log.hpp>
#include <sprout/complex/sqrt.hpp>

namespace sprout {
	//
	// asinh
	//
	// G.6.2.2 The casinh functions
	// casinh(conj(z)) = conj(casinh(z)) and casinh is odd.
	// casinh(+0 + i0) returns 0 + i0.
	// casinh(x + iÅá) returns +Åá+ ip /2 for positive-signed finite x.
	// casinh(x + iNaN) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for finite x.
	// casinh(+Åá+ iy) returns +Åá+ i0 for positive-signed finite y.
	// casinh(+Åá+ iÅá) returns +Åá+ ip /4.
	// casinh(+Åá+ iNaN) returns +Åá+ iNaN.
	// casinh(NaN + i0) returns NaN + i0.
	// casinh(NaN + iy) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for finite nonzero y.
	// casinh(NaN + iÅá) returns Å}Åá+ iNaN (where the sign of the real part of the result is unspecified).
	// casinh(NaN + iNaN) returns NaN + iNaN.
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	asinh(sprout::complex<T> const& x) {
		typedef sprout::complex<T> type;
		return sprout::math::isnan(x.real())
				? sprout::math::isnan(x.imag()) ? x
				: sprout::math::isinf(x.imag()) ? type(x.imag(), x.real())
				: x.imag() == 0 ? x
				: type(x.real(), x.real())
			: sprout::math::isnan(x.imag())
				? sprout::math::isinf(x.real()) ? x
				: type(sprout::math::copysign(sprout::numeric_limits<T>::quiet_NaN(), x.real()), x.imag())
			: sprout::math::isinf(x.real())
				? x.imag() == sprout::numeric_limits<T>::infinity() ? type(x.real(), sprout::math::quarter_pi<T>())
				: x.imag() == -sprout::numeric_limits<T>::infinity() ? type(x.real(), -sprout::math::quarter_pi<T>())
				: x.imag() == 0 ? x
				: type(x.real(), (x.imag() == 0 ? x.imag() : sprout::math::copysign(T(0), x.imag())))
			: sprout::math::isinf(x.imag()) ? type(
				sprout::math::copysign(sprout::numeric_limits<T>::infinity(), x.real()),
				sprout::math::copysign(sprout::math::half_pi<T>(), x.imag())
				)
			: x.real() == 0 && x.imag() == 0 ? x
			: sprout::log(sprout::sqrt(type((x.real() - x.imag()) * (x.real() + x.imag()) + T(1), T(2) * x.real() * x.imag())) + x)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_ASINH_HPP
