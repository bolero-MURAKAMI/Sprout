/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_CALL_FUN_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_CALL_FUN_HPP

#include <sprout/config.hpp>
#include <sprout/functional/call_fun.hpp>

namespace sprout {
	//
	// call_fun_t
	// call_fun_
	//
	typedef sprout::call_fun<> call_fun_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::call_fun_t call_fun_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_CALL_FUN_HPP
