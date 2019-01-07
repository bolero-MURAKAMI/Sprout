/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_IS_PARTITIONED_HPP
#define SPROUT_RANGE_ALGORITHM_IS_PARTITIONED_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_partitioned.hpp>

namespace sprout {
	namespace range {

		// 25.3.13 partitions
		template<typename InputRange, typename Predicate>
		inline SPROUT_CONSTEXPR bool
		is_partitioned(InputRange const& range, Predicate pred) {
			return sprout::is_partitioned(sprout::begin(range), sprout::end(range), pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_PARTITIONED_HPP
