/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_POST_INC_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_POST_INC_HPP

#include <sprout/config.hpp>
#include <sprout/functional/post_inc.hpp>

namespace sprout {
	//
	// post_inc_t
	// post_inc_
	//
	typedef sprout::post_inc<> post_inc_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::post_inc_t post_inc_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_POST_INC_HPP
