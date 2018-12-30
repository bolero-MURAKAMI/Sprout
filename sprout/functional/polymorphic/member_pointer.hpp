/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_MEMBER_POINTER_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_MEMBER_POINTER_HPP

#include <sprout/config.hpp>
#include <sprout/functional/member_pointer.hpp>

namespace sprout {
	//
	// member_pointer_t
	// member_pointer_
	//
	typedef sprout::member_pointer<> member_pointer_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::member_pointer_t member_pointer_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_MEMBER_POINTER_HPP
