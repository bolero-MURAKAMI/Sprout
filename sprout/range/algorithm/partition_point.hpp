#ifndef SPROUT_RANGE_ALGORITHM_PARTITION_POINT_HPP
#define SPROUT_RANGE_ALGORITHM_PARTITION_POINT_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/partition_point.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.3.13 partitions
		template<typename Range, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range>::type
		partition_point(Range&& range, Predicate pred) {
			return sprout::range::range_return<Range>::pack(
				sprout::partition_point(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					pred
					),
				sprout::forward<Range>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_PARTITION_POINT_HPP
