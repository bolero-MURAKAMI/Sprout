/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2019 Bolero MURAKAMI
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
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					pred
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_PARTITION_POINT_HPP
