#ifndef SPROUT_RANGE_ALGORITHM_BINARY_SEARCH_HPP
#define SPROUT_RANGE_ALGORITHM_BINARY_SEARCH_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/binary_search.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.4.3.4 binary_search
		template<typename Range, typename T>
		inline SPROUT_CONSTEXPR bool binary_search(Range const& range, T const& value) {
			return sprout::binary_search(sprout::begin(range), sprout::end(range), value);
		}

		template<typename Range, typename T, typename Compare>
		inline SPROUT_CONSTEXPR bool binary_search(Range const& range, T const& value, Compare comp) {
			return sprout::binary_search(sprout::begin(range), sprout::end(range), value, comp);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_BINARY_SEARCH_HPP
