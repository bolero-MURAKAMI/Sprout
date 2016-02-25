/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_AS_LVALUE_HPP
#define SPROUT_UTILITY_AS_LVALUE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// as_lvalue
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T&
	as_lvalue(T& t) {
		return t;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR T const&
	as_lvalue(T const& t) {
		return t;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_AS_LVALUE_HPP
