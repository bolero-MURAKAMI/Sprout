#ifndef SPROUT_RANGE_ALGORITHM_SEARCH_HPP
#define SPROUT_RANGE_ALGORITHM_SEARCH_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/operation.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/search.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.13 Search
		template<typename Range1, typename Range2>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range1>::type
		search(Range1&& range1, Range2&& range2) {
			return sprout::range::range_return<Range1>::pack(
				sprout::search(
					sprout::begin(sprout::forward<Range1>(range1)),
					sprout::end(sprout::forward<Range1>(range1)),
					sprout::begin(sprout::forward<Range2>(range2)),
					sprout::end(sprout::forward<Range2>(range2))
					),
				sprout::forward<Range1>(range1)
				);
		}

		template<typename Range1, typename Range2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range1>::type
		search(Range1&& range1, Range2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<Range1>::pack(
				sprout::search(
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
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range1, RetV>::type
		search(Range1&& range1, Range2&& range2) {
			return sprout::range::range_return<Range1, RetV>::pack(
				sprout::search(
					sprout::begin(sprout::forward<Range1>(range1)),
					sprout::end(sprout::forward<Range1>(range1)),
					sprout::begin(sprout::forward<Range2>(range2)),
					sprout::end(sprout::forward<Range2>(range2))
					),
				sprout::forward<Range1>(range1)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range1, typename Range2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range1, RetV>::type
		search(Range1&& range1, Range2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<Range1, RetV>::pack(
				sprout::search(
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

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_SEARCH_HPP
