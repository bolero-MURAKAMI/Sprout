#ifndef SPROUT_RANGE_ALGORITHM_IS_PERMUTATION_HPP
#define SPROUT_RANGE_ALGORITHM_IS_PERMUTATION_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_permutation.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.12 Is permutation
		template<typename Range1, typename Range2>
		inline SPROUT_CONSTEXPR bool is_permutation(Range1 const& range1, Range2 const& range2) {
			return sprout::is_permutation(sprout::begin(range1), sprout::end(range1), sprout::begin(range2));
		}

		template<typename Range1, typename Range2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool is_permutation(Range1 const& range1, Range2 const& range2, BinaryPredicate pred) {
			return sprout::is_permutation(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_PERMUTATION_HPP
