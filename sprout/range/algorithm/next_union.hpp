#ifndef SPROUT_RANGE_ALGORITHM_NEXT_UNION_HPP
#define SPROUT_RANGE_ALGORITHM_NEXT_UNION_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/range/type_traits/lvalue_iterator.hpp>
#include <sprout/algorithm/next_union.hpp>

namespace sprout {
	namespace range {
		//
		// next_union
		//
		template<typename Range1, typename Range2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::lvalue_iterator<Range1>::type,
			typename sprout::range::lvalue_iterator<Range2>::type
		>
		next_union(Range1&& range1, Range2&& range2, Compare comp) {
			return sprout::next_union(
				sprout::begin(sprout::forward<Range1>(range1)),
				sprout::end(sprout::forward<Range1>(range1)),
				sprout::begin(sprout::forward<Range2>(range2)),
				sprout::end(sprout::forward<Range2>(range2)),
				comp
				);
		}

		template<typename Range1, typename Range2>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::lvalue_iterator<Range1>::type,
			typename sprout::range::lvalue_iterator<Range2>::type
		>
		next_union(Range1&& range1, Range2&& range2) {
			return sprout::next_union(
				sprout::begin(sprout::forward<Range1>(range1)),
				sprout::end(sprout::forward<Range1>(range1)),
				sprout::begin(sprout::forward<Range2>(range2)),
				sprout::end(sprout::forward<Range2>(range2))
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_NEXT_UNION_HPP
