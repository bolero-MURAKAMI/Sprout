/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_IGNORE_UNUSED_HPP
#define SPROUT_UTILITY_IGNORE_UNUSED_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// ignore_unused
	//
	inline SPROUT_CXX14_CONSTEXPR void
	ignore_unused(...) SPROUT_NOEXCEPT {}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_IGNORE_UNUSED_HPP
