#ifndef SPROUT_RANGE_ALGORITHM_IS_PARTITIONED_HPP
#define SPROUT_RANGE_ALGORITHM_IS_PARTITIONED_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_partitioned.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.3.13 partitions
		template<typename Range, typename Predicate>
		SPROUT_CONSTEXPR bool is_partitioned(Range const& range, Predicate pred) {
			return sprout::is_partitioned(sprout::begin(range), sprout::end(range), pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_PARTITIONED_HPP
