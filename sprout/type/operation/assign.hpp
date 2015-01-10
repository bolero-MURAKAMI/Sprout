/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_ASSIGN_HPP
#define SPROUT_TYPE_OPERATION_ASSIGN_HPP

#include <sprout/config.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/type/operation/tuple_cat.hpp>

namespace sprout {
	namespace types {
		//
		// assign
		//
		template<typename Tuple, typename InputTuple>
		struct assign
			: public sprout::types::tuple_cat<
				typename sprout::types::apply<sprout::types::rebind_types<Tuple> >::type,
				InputTuple
			>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename InputTuple>
		using assign_t = typename sprout::types::assign<Tuple, InputTuple>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_ASSIGN_HPP
