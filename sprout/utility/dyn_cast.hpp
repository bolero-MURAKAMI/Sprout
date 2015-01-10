/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_DYN_CAST_HPP
#define SPROUT_UTILITY_DYN_CAST_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/is_upcast.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// dyn_cast
	//
	template<
		typename T, typename U,
		typename sprout::enabler_if<sprout::is_upcast<U&&, T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR T
	dyn_cast(U&& x) {
		return static_cast<T>(SPROUT_FORWARD(U, x));
	}
	template<
		typename T, typename U,
		typename sprout::enabler_if<!sprout::is_upcast<U&&, T>::value>::type = sprout::enabler
	>
	inline SPROUT_NON_CONSTEXPR T
	dyn_cast(U&& x) {
		return dynamic_cast<T>(SPROUT_FORWARD(U, x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_DYN_CAST_HPP
