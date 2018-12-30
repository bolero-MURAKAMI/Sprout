/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_LOG_HPP
#define SPROUT_COMPLEX_LOG_HPP

#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/log.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/abs.hpp>
#include <sprout/complex/arg.hpp>

namespace sprout {
	//
	// log
	//
	// G.6.3.2 The clog functions
	// clog(conj(z)) = conj(clog(z)).
	// clog(-0 + i0) returns -Åá+ ip and raises the ÅeÅedivide-by-zeroÅfÅf floating-point exception.
	// clog(+0 + i0) returns -Åá+ i0 and raises the ÅeÅedivide-by-zeroÅfÅf floating-point exception.
	// clog(x + iÅá) returns +Åá+ ip /2, for finite x.
	// clog(x + iNaN) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for finite x.
	// clog(-Åá+ iy) returns +Åá+ ip , for finite positive-signed y.
	// clog(+Åá+ iy) returns +Åá+ i0, for finite positive-signed y.
	// clog(-Åá+ iÅá) returns +Åá+ i3p /4.
	// clog(+Åá+ iÅá) returns +Åá+ ip /4.
	// clog(Å}Åá+ iNaN) returns +Åá+ iNaN.
	// clog(NaN + iy) returns NaN + iNaN and optionally raises the ÅeÅeinvalidÅfÅf floating-point exception, for finite y.
	// clog(NaN + iÅá) returns +Åá+ iNaN.
	// clog(NaN + iNaN) returns NaN + iNaN.
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	log(sprout::complex<T> const& x) {
		typedef sprout::complex<T> type;
		return sprout::math::isnan(x.real())
				? sprout::math::isnan(x.imag()) ? type(sprout::numeric_limits<T>::quiet_NaN(), x.real())
				: sprout::math::isinf(x.imag()) ? type(sprout::numeric_limits<T>::infinity(), x.real())
				: type(sprout::numeric_limits<T>::quiet_NaN(), x.real())
			: sprout::math::isnan(x.imag())
				? sprout::math::isinf(x.real()) ? type(sprout::numeric_limits<T>::infinity(), x.imag())
				: type(sprout::numeric_limits<T>::quiet_NaN(), x.imag())
			: x.real() == sprout::numeric_limits<T>::infinity()
				? x.imag() == sprout::numeric_limits<T>::infinity() ? type(sprout::numeric_limits<T>::infinity(), sprout::math::quarter_pi<T>())
				: x.imag() == -sprout::numeric_limits<T>::infinity() ? type(sprout::numeric_limits<T>::infinity(), -sprout::math::quarter_pi<T>())
				: type(sprout::numeric_limits<T>::infinity(), (x.imag() == 0 ? x.imag() : sprout::math::copysign(T(0), x.imag())))
			: x.real() == -sprout::numeric_limits<T>::infinity()
				? x.imag() == sprout::numeric_limits<T>::infinity() ? type(sprout::numeric_limits<T>::infinity(), sprout::math::three_quarters_pi<T>())
				: x.imag() == -sprout::numeric_limits<T>::infinity() ? type(sprout::numeric_limits<T>::infinity(), -sprout::math::three_quarters_pi<T>())
				: type(sprout::numeric_limits<T>::infinity(), sprout::math::copysign(sprout::math::pi<T>(), x.imag()))
			: sprout::math::isinf(x.imag()) ? type(sprout::numeric_limits<T>::infinity(), sprout::math::copysign(sprout::math::half_pi<T>(), x.imag()))
			: x.real() == 0 && x.imag() == 0
				? sprout::math::signbit(x.real()) ? type(-sprout::numeric_limits<T>::infinity(), sprout::math::copysign(sprout::math::pi<T>(), x.imag()))
				: type(-sprout::numeric_limits<T>::infinity(), x.imag())
			: type(sprout::math::log(sprout::abs(x)), sprout::arg(x))
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_LOG_HPP
