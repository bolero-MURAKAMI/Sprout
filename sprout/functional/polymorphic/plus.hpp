/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_PLUS_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_PLUS_HPP

#include <sprout/config.hpp>
#include <sprout/functional/plus.hpp>

namespace sprout {
	//
	// plus_t
	// plus_
	//
	typedef sprout::plus<> plus_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::plus_t plus_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_PLUS_HPP
