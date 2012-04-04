#ifndef SPROUT_RANGE_ALGORITHM_UPPER_BOUND_HPP
#define SPROUT_RANGE_ALGORITHM_UPPER_BOUND_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/operation.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/upper_bound.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.4.3.2 upper_bound
		template<typename Range, typename T>
		SPROUT_CONSTEXPR typename sprout::range::range_return<Range>::type
		upper_bound(Range&& range, T const& value) {
			return sprout::range::range_return<Range>::pack(
				sprout::upper_bound(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					value
					),
				sprout::forward<Range>(range)
				);
		}

		template<typename Range, typename T, typename Compare>
		SPROUT_CONSTEXPR typename sprout::range::range_return<Range>::type
		upper_bound(Range&& range, T const& value, Compare comp) {
			return sprout::range::range_return<Range>::pack(
				sprout::upper_bound(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					value,
					comp
					),
				sprout::forward<Range>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range, typename T>
		SPROUT_CONSTEXPR typename sprout::range::range_return<Range, RetV>::type
		upper_bound(Range&& range, T const& value) {
			return sprout::range::range_return<Range, RetV>::pack(
				sprout::upper_bound(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					value
					),
				sprout::forward<Range>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range, typename T, typename Compare>
		SPROUT_CONSTEXPR typename sprout::range::range_return<Range, RetV>::type
		upper_bound(Range&& range, T const& value, Compare comp) {
			return sprout::range::range_return<Range, RetV>::pack(
				sprout::upper_bound(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					value,
					comp
					),
				sprout::forward<Range>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_UPPER_BOUND_HPP
