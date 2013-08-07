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
		template<typename ForwardRange, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		partition_point(ForwardRange&& range, Predicate pred) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::partition_point(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range)),
					pred
					),
				sprout::forward<ForwardRange>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_PARTITION_POINT_HPP
