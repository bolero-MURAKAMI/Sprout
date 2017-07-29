/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_IS_HEAP_HPP
#define SPROUT_RANGE_ALGORITHM_IS_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_heap.hpp>

namespace sprout {
	namespace range {

		// 25.4.6.5 is_heap
		template<typename RandomAccessRange>
		inline SPROUT_CONSTEXPR bool
		is_heap(RandomAccessRange const& range) {
			return sprout::is_heap(sprout::begin(range), sprout::end(range));
		}

		template<typename RandomAccessRange, typename Compare>
		inline SPROUT_CONSTEXPR bool
		is_heap(RandomAccessRange const& range, Compare comp) {
			return sprout::is_heap(sprout::begin(range), sprout::end(range), comp);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_HEAP_HPP
