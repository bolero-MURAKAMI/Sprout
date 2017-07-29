/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_POP_FRONT_HPP
#define SPROUT_TYPE_OPERATION_POP_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/pop_front_types.hpp>

namespace sprout {
	namespace types {
		//
		// pop_front
		//
		template<typename Tuple>
		struct pop_front
			: public sprout::types::apply<sprout::types::pop_front_types<Tuple> >
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple>
		using pop_front_t = typename sprout::types::pop_front<Tuple>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_POP_FRONT_HPP
