#ifndef SPROUT_RANGE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
#define SPROUT_RANGE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/lexicographical_compare.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.4.8 Lexicographical comparison
		template<typename Range1, typename Range2>
		inline SPROUT_CONSTEXPR bool
		lexicographical_compare(Range1 const& range1, Range2 const& range2) {
			return sprout::lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2)
				);
		}

		template<typename Range1, typename Range2, typename Compare>
		inline SPROUT_CONSTEXPR bool
		lexicographical_compare(Range1 const& range1, Range2 const& range2, Compare comp) {
			return sprout::lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2), comp
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
