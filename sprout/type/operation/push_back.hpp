/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_PUSH_BACK_HPP
#define SPROUT_TYPE_OPERATION_PUSH_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/type/type_tuple.hpp>
#include <sprout/type/operation/tuple_cat.hpp>

namespace sprout {
	namespace types {
		//
		// push_back
		//
		template<typename Tuple, typename... Ts>
		struct push_back
			: public sprout::types::tuple_cat<Tuple, sprout::types::type_tuple<Ts...> >
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename... Ts>
		using push_back_t = typename sprout::types::push_back<Tuple, Ts...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_PUSH_BACK_HPP
