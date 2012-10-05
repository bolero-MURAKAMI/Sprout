#ifndef SPROUT_RANGE_ALGORITHM_MISMATCH_HPP
#define SPROUT_RANGE_ALGORITHM_MISMATCH_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair.hpp>
#include <sprout/range/lvalue_iterator.hpp>
#include <sprout/algorithm/mismatch.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.10 Mismatch
		template<typename Range1, typename Range2>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::lvalue_iterator<Range1>::type,
			typename sprout::range::lvalue_iterator<Range2>::type
		>
		mismatch(Range1&& range1, Range2&& range2) {
			return sprout::mismatch(
				sprout::begin(sprout::forward<Range1>(range1)),
				sprout::end(sprout::forward<Range1>(range1)),
				sprout::begin(sprout::forward<Range2>(range2))
				);
		}

		template<typename Range1, typename Range2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::lvalue_iterator<Range1>::type,
			typename sprout::range::lvalue_iterator<Range2>::type
		>
		mismatch(Range1&& range1, Range2&& range2, BinaryPredicate pred) {
			return sprout::mismatch(
				sprout::begin(sprout::forward<Range1>(range1)),
				sprout::end(sprout::forward<Range1>(range1)),
				sprout::begin(sprout::forward<Range2>(range2)),
				pred
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_MISMATCH_HPP
