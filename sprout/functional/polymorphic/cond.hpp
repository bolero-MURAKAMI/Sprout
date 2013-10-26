/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_COND_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_COND_HPP

#include <sprout/config.hpp>
#include <sprout/functional/cond.hpp>

namespace sprout {
	//
	// cond_t
	// cond_
	//
	typedef sprout::cond<> cond_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::cond_t cond_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_COND_HPP
