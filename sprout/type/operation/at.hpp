/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_AT_HPP
#define SPROUT_TYPE_OPERATION_AT_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		//
		// at
		//
		template<typename Tuple, std::size_t I>
		struct at
			: public sprout::types::tuple_element<I, Tuple>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, std::size_t I>
		using at_t = typename sprout::types::at<Tuple, I>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_AT_HPP
