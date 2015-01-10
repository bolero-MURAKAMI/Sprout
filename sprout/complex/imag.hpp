/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_IMAG_HPP
#define SPROUT_COMPLEX_IMAG_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// imag
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T const&
	imag(sprout::complex<T> const& x) {
		return x.imag();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR T&
	imag(sprout::complex<T>& x) {
		return x.imag();
	}
	template<
		typename ArithmeticType,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
	imag(ArithmeticType) {
		return 0;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_IMAG_HPP
