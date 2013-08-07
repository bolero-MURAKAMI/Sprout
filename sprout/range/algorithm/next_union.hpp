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
		template<typename InputRange1, typename InputRange2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::lvalue_iterator<InputRange1>::type,
			typename sprout::range::lvalue_iterator<InputRange2>::type
		>
		next_union(InputRange1&& range1, InputRange2&& range2, Compare comp) {
			return sprout::next_union(
				sprout::begin(sprout::forward<InputRange1>(range1)),
				sprout::end(sprout::forward<InputRange1>(range1)),
				sprout::begin(sprout::forward<InputRange2>(range2)),
				sprout::end(sprout::forward<InputRange2>(range2)),
				comp
				);
		}

		template<typename InputRange1, typename InputRange2>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::lvalue_iterator<InputRange1>::type,
			typename sprout::range::lvalue_iterator<InputRange2>::type
		>
		next_union(InputRange1&& range1, InputRange2&& range2) {
			return sprout::next_union(
				sprout::begin(sprout::forward<InputRange1>(range1)),
				sprout::end(sprout::forward<InputRange1>(range1)),
				sprout::begin(sprout::forward<InputRange2>(range2)),
				sprout::end(sprout::forward<InputRange2>(range2))
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_NEXT_UNION_HPP
