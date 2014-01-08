/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_MEM_PTR_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_MEM_PTR_HPP

#include <sprout/config.hpp>
#include <sprout/functional/mem_ptr.hpp>

namespace sprout {
	//
	// mem_ptr_t
	// mem_ptr_
	//
	typedef sprout::mem_ptr<> mem_ptr_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::mem_ptr_t mem_ptr_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_MEM_PTR_HPP
