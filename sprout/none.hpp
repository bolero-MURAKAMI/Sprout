/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NONE_HPP
#define SPROUT_NONE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// none_t
	// none
	//
	struct none_t {};
	namespace {
		SPROUT_STATIC_CONSTEXPR none_t none = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_NONE_HPP
