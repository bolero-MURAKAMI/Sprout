/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_PRE_INCREMENT_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_PRE_INCREMENT_HPP

#include <sprout/config.hpp>
#include <sprout/functional/pre_increment.hpp>

namespace sprout {
	//
	// pre_increment_t
	// pre_increment_
	//
	typedef sprout::pre_increment<> pre_increment_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::pre_increment_t pre_increment_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_PRE_INCREMENT_HPP
