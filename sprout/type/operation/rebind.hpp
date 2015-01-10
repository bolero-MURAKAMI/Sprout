/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_REBIND_HPP
#define SPROUT_TYPE_OPERATION_REBIND_HPP

#include <sprout/config.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/rebind_types.hpp>

namespace sprout {
	namespace types {
		//
		// rebind
		//
		template<typename Tuple, typename... Ts>
		struct rebind
			: public sprout::types::apply<sprout::types::rebind_types<Tuple>, Ts...>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename... Ts>
		using rebind_t = typename sprout::types::rebind<Tuple, Ts...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_REBIND_HPP
