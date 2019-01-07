/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_ACCUMLATE_HPP
#define SPROUT_TYPE_ALGORITHM_ACCUMLATE_HPP

#include <sprout/config.hpp>
#include <sprout/type/algorithm/fold.hpp>
#include <sprout/type/functional/plus.hpp>

namespace sprout {
	namespace types {
		//
		// accumulate
		//
		template<typename Tuple, typename T, typename BinaryOp = sprout::types::plus_>
		struct accumulate
			: public sprout::types::fold<Tuple, T, BinaryOp>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename T, typename BinaryOp = sprout::types::plus_>
		using accumulate_t = typename sprout::types::accumulate<Tuple, T, BinaryOp>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_ACCUMLATE_HPP
