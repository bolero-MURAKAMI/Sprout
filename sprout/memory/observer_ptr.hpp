/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MEMORY_OBSERVER_PTR_HPP
#define SPROUT_MEMORY_OBSERVER_PTR_HPP

#include <sprout/config.hpp>
#include <sprout/memory/exempt_ptr.hpp>

namespace sprout {
	//
	// make_observer
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::exempt_ptr<T>
	make_observer(T* p) SPROUT_NOEXCEPT {
		return sprout::exempt_ptr<T>(p);
	}

#if SPROUT_USE_TEMPLATE_ALIASES
	//
	// observer_ptr
	//
	template<typename T>
	using observer_ptr = sprout::exempt_ptr<T>;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_MEMORY_OBSERVER_PTR_HPP
