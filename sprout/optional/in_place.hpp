/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPTIONAL_IN_PLACE_HPP
#define SPROUT_OPTIONAL_IN_PLACE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// in_place_t
	// in_place
	//
	struct in_place_t {};
	namespace {
		SPROUT_STATIC_CONSTEXPR in_place_t in_place{};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_IN_PLACE_HPP
