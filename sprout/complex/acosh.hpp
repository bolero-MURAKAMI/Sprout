/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_ACOSH_HPP
#define SPROUT_COMPLEX_ACOSH_HPP

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
	// acosh
	//
	// G.6.2.1 The cacosh functions
	// cacosh(conj(z)) = conj(cacosh(z)).
	// cacosh(Å}0 + i0) returns +0 + ip /2.
	// cacosh(x + iÅá) returns +Åá+ ip /2, for finite x.
	// cacosh(x + iNaN) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for finite x.
	// cacosh(-Åá+ iy) returns +Åá+ ip , for positive-signed finite y.
	// cacosh(+Åá+ iy) returns +Åá+ i0, for positive-signed finite y.
	// cacosh(-Åá+ iÅá) returns +Åá+ i3p /4.
	// cacosh(+Åá+ iÅá) returns +Åá+ ip /4.
	// cacosh(Å}Åá+ iNaN) returns +Åá+ iNaN.
	// cacosh(NaN + iy) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for finite y.
	// cacosh(NaN + iÅá) returns +Åá+ iNaN.
	// cacosh(NaN + iNaN) returns NaN + iNaN.
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	acosh(sprout::complex<T> const& x) {
		typedef sprout::complex<T> type;
		return sprout::math::isnan(x.real())
				? sprout::math::isnan(x.imag()) ? x
				: sprout::math::isinf(x.imag()) ? type(sprout::numeric_limits<T>::infinity(), x.real())
				: type(x.real(), x.real())
			: sprout::math::isnan(x.imag())
				? sprout::math::isinf(x.real()) ? type(sprout::numeric_limits<T>::infinity(), x.imag())
				: type(sprout::numeric_limits<T>::quiet_NaN(), x.imag())
			: x.real() == sprout::numeric_limits<T>::infinity()
				? sprout::math::isinf(x.imag()) ? type(sprout::numeric_limits<T>::infinity(), sprout::math::copysign(sprout::math::quarter_pi<T>(), x.imag()))
				: type(sprout::numeric_limits<T>::infinity(), (x.imag() == 0 ? x.imag() : sprout::math::copysign(T(0), x.imag())))
			: x.real() == -sprout::numeric_limits<T>::infinity()
				? sprout::math::isinf(x.imag()) ? type(sprout::numeric_limits<T>::infinity(), sprout::math::copysign(sprout::math::three_quarters_pi<T>(), x.imag()))
				: type(sprout::numeric_limits<T>::infinity(), sprout::math::copysign(sprout::math::pi<T>(), x.imag()))
			: sprout::math::isinf(x.imag()) ? type(sprout::numeric_limits<T>::infinity(), sprout::math::copysign(sprout::math::half_pi<T>(), x.imag()))
			: x.real() == 0 && x.imag() == 0 ? type(T(0), sprout::math::copysign(sprout::math::half_pi<T>(), x.imag()))
			: T(2) * sprout::log(sprout::sqrt(sprout::math::half<T>() * (x + T(1))) + sprout::sqrt(sprout::math::half<T>() * (x - T(1))))
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_ACOSH_HPP
