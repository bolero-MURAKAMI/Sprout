/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_PARTITION_POINT_HPP
#define SPROUT_RANGE_ALGORITHM_PARTITION_POINT_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/partition_point.hpp>

namespace sprout {
	namespace range {

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
