/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_NORM_HPP
#define SPROUT_COMPLEX_NORM_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/complex/complex.hpp>

namespace sprout {
	//
	// norm
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T
	norm(sprout::complex<T> const& x) {
		return sprout::math::isinf(x.imag()) || sprout::math::isinf(x.real()) ? sprout::numeric_limits<T>::infinity()
			: sprout::math::isnan(x.real()) ? x.real()
			: sprout::math::isnan(x.imag()) ? x.imag()
			: x.real() * x.real() + x.imag() * x.imag()
			;
	}
	template<
		typename ArithmeticType,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
	norm(ArithmeticType x) {
		typedef typename sprout::float_promote<ArithmeticType>::type type;
		return sprout::math::isinf(x) ? sprout::numeric_limits<type>::infinity()
			: sprout::math::isnan(x) ? type(x)
			: type(x) * type(x)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_NORM_HPP
