/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_PROJ_HPP
#define SPROUT_COMPLEX_PROJ_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/type_traits/complex_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// proj
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	proj(sprout::complex<T> const& x) {
		typedef sprout::complex<T> type;
		return sprout::math::isinf(x.real()) || sprout::math::isinf(x.imag())
			? type(sprout::numeric_limits<T>::infinity(), sprout::math::copysign(T(), x.imag()))
			: x
			;
	}
	template<
		typename ArithmeticType,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::complex_promote<ArithmeticType>::type
	proj(ArithmeticType x) {
		typedef typename sprout::complex_promote<ArithmeticType>::type type;
		return sprout::math::isinf(x)
			? type(sprout::numeric_limits<ArithmeticType>::infinity())
			: type(x)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_PROJ_HPP
