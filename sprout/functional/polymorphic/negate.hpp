/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_NEGATE_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_NEGATE_HPP

#include <sprout/config.hpp>
#include <sprout/functional/negate.hpp>

namespace sprout {
	//
	// negate_t
	// negate_
	//
	typedef sprout::negate<> negate_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::negate_t negate_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_NEGATE_HPP
