/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_CONJ_HPP
#define SPROUT_COMPLEX_CONJ_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/type_traits/complex_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// conj
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	conj(sprout::complex<T> const& x) {
		return sprout::complex<T>(x.real(), -x.imag());
	}
	template<
		typename ArithmeticType,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::complex_promote<ArithmeticType>::type
	conj(ArithmeticType x) {
		typedef typename sprout::complex_promote<ArithmeticType>::type type;
		return type(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_CONJ_HPP
