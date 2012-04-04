#ifndef SPROUT_RANGE_ALGORITHM_FIND_FIRST_OF_HPP
#define SPROUT_RANGE_ALGORITHM_FIND_FIRST_OF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/operation.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/find_first_of.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.7 Find first
		template<typename Range1, typename Range2>
		SPROUT_CONSTEXPR typename sprout::range::range_return<Range1>::type
		find_first_of(Range1&& range1, Range2&& range2) {
			return sprout::range::range_return<Range1>::pack(
				sprout::find_first_of(
					sprout::begin(sprout::forward<Range1>(range1)),
					sprout::end(sprout::forward<Range1>(range1)),
					sprout::begin(sprout::forward<Range2>(range2)),
					sprout::end(sprout::forward<Range2>(range2))
					),
				sprout::forward<Range1>(range1)
				);
		}

		template<typename Range1, typename Range2, typename BinaryPredicate>
		SPROUT_CONSTEXPR typename sprout::range::range_return<Range1>::type
		find_first_of(Range1&& range1, Range2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<Range1>::pack(
				sprout::find_first_of(
					sprout::begin(sprout::forward<Range1>(range1)),
					sprout::end(sprout::forward<Range1>(range1)),
					sprout::begin(sprout::forward<Range2>(range2)),
					sprout::end(sprout::forward<Range2>(range2)),
					pred
					),
				sprout::forward<Range1>(range1)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range1, typename Range2>
		SPROUT_CONSTEXPR typename sprout::range::range_return<Range1, RetV>::type
		find_first_of(Range1&& range1, Range2&& range2) {
			return sprout::range::range_return<Range1, RetV>::pack(
				sprout::find_first_of(
					sprout::begin(sprout::forward<Range1>(range1)),
					sprout::end(sprout::forward<Range1>(range1)),
					sprout::begin(sprout::forward<Range2>(range2)),
					sprout::end(sprout::forward<Range2>(range2))
					),
				sprout::forward<Range1>(range1)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range1, typename Range2, typename BinaryPredicate>
		SPROUT_CONSTEXPR typename sprout::range::range_return<Range1, RetV>::type
		find_first_of(Range1&& range1, Range2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<Range1, RetV>::pack(
				sprout::find_first_of(
					sprout::begin(sprout::forward<Range1>(range1)),
					sprout::end(sprout::forward<Range1>(range1)),
					sprout::begin(sprout::forward<Range2>(range2)),
					sprout::end(sprout::forward<Range2>(range2)),
					pred
					),
				sprout::forward<Range1>(range1)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIND_FIRST_OF_HPP
