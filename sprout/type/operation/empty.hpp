/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_EMPTY_HPP
#define SPROUT_TYPE_OPERATION_EMPTY_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		//
		// empty
		//
		template<typename Tuple>
		struct empty
			: public sprout::bool_constant<
				(sprout::types::tuple_size<Tuple>::value == 0)
			>
		{};

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple>
		SPROUT_STATIC_CONSTEXPR bool empty_v = sprout::types::empty<Tuple>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_EMPTY_HPP
