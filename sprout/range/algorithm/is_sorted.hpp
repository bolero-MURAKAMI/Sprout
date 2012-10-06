#ifndef SPROUT_RANGE_ALGORITHM_IS_SORTED_HPP
#define SPROUT_RANGE_ALGORITHM_IS_SORTED_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_sorted.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.4.1.5 is_sorted
		template<typename Range>
		inline SPROUT_CONSTEXPR bool
		is_sorted(Range const& range) {
			return sprout::is_sorted(sprout::begin(range), sprout::end(range));
		}

		template<typename Range, typename Compare>
		inline SPROUT_CONSTEXPR bool
		is_sorted(Range const& range, Compare comp) {
			return sprout::is_sorted(sprout::begin(range), sprout::end(range), comp);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_SORTED_HPP
