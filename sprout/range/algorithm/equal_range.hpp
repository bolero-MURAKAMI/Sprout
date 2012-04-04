#ifndef SPROUT_RANGE_ALGORITHM_EQUAL_RANGE_HPP
#define SPROUT_RANGE_ALGORITHM_EQUAL_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/operation.hpp>
#include <sprout/range/lvref_range.hpp>
#include <sprout/algorithm/equal_range.hpp>

namespace sprout {
	namespace range {
		namespace detail {
			template<typename Range, typename Pair>
			inline SPROUT_CONSTEXPR typename sprout::range::lvref_range<Range>::type
			pair_to_range(Pair const& pair) {
				return {pair.first, pair.second};
			}
		}	// namespace detail

		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.4.3.3 equal_range
		template<typename Range, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::lvref_range<Range>::type
		equal_range(Range&& range, T const& value) {
			return sprout::range::detail::pair_to_range<Range>(
				sprout::equal_range(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					value
					)
				);
		}

		template<typename Range, typename T, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::lvref_range<Range>::type
		equal_range(Range&& range, T const& value, Compare comp) {
			return sprout::range::detail::pair_to_range<Range>(
				sprout::equal_range(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					value,
					comp
					)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_EQUAL_RANGE_HPP
