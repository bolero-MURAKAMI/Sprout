/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_APPEND_BACK_HPP
#define SPROUT_TYPE_OPERATION_APPEND_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/type/operation/tuple_cat.hpp>

namespace sprout {
	namespace types {
		//
		// append_back
		//
		template<typename Tuple, typename... InputTuples>
		struct append_back
			: public sprout::types::tuple_cat<Tuple, InputTuples...>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename... InputTuples>
		using append_back_t = typename sprout::types::append_back<Tuple, InputTuples...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_APPEND_BACK_HPP
