/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_IMPLICIT_CAST_HPP
#define SPROUT_UTILITY_IMPLICIT_CAST_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	//
	// implicit_cast
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T
	implicit_cast(typename sprout::identity<T>::type t) {
	    return t;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_IMPLICIT_CAST_HPP
