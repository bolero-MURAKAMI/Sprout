/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_SWALLOW_HPP
#define SPROUT_UTILITY_SWALLOW_HPP

#include <initializer_list>
#include <sprout/config.hpp>

namespace sprout {
	//
	// swallow
	//
	template<typename T>
	inline SPROUT_CXX14_CONSTEXPR void
	swallow(std::initializer_list<T>) SPROUT_NOEXCEPT {}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_SWALLOW_HPP
