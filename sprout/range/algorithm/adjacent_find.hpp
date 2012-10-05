#ifndef SPROUT_RANGE_ALGORITHM_ADJACENT_FIND_HPP
#define SPROUT_RANGE_ALGORITHM_ADJACENT_FIND_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/adjacent_find.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.8 Adjacent find
		template<typename Range>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range>::type
		adjacent_find(Range&& range) {
			return sprout::range::range_return<Range>::pack(
				sprout::adjacent_find(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range))
					),
				sprout::forward<Range>(range)
				);
		}

		template<typename Range, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range>::type
		adjacent_find(Range&& range, BinaryPredicate pred) {
			return sprout::range::range_return<Range>::pack(
				sprout::adjacent_find(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					pred
					),
				sprout::forward<Range>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range, RetV>::type
		adjacent_find(Range&& range) {
			return sprout::range::range_return<Range, RetV>::pack(
				sprout::adjacent_find(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range))
					),
				sprout::forward<Range>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<Range, RetV>::type
		adjacent_find(Range&& range, BinaryPredicate pred) {
			return sprout::range::range_return<Range, RetV>::pack(
				sprout::adjacent_find(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					pred
					),
				sprout::forward<Range>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_ADJACENT_FIND_HPP
