/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_PUSH_FRONT_HPP
#define SPROUT_TYPE_OPERATION_PUSH_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/type/type_tuple.hpp>
#include <sprout/type/operation/tuple_cat.hpp>

namespace sprout {
	namespace types {
		//
		// push_front
		//
		template<typename Tuple, typename... Ts>
		struct push_front
			: public sprout::types::tuple_cat<
				typename sprout::types::rebind_types<Tuple>::template apply<>::type,
				sprout::types::type_tuple<Ts...>, Tuple
			>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename... Ts>
		using push_front_t = typename sprout::types::push_front<Tuple, Ts...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_PUSH_FRONT_HPP
