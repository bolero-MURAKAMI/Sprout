#ifndef SPROUT_RANGE_ALGORITHM_UPPER_BOUND_HPP
#define SPROUT_RANGE_ALGORITHM_UPPER_BOUND_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/upper_bound.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.4.3.2 upper_bound
		template<typename ForwardRange, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		upper_bound(ForwardRange&& range, T const& value) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::upper_bound(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range)),
					value
					),
				sprout::forward<ForwardRange>(range)
				);
		}

		template<typename ForwardRange, typename T, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		upper_bound(ForwardRange&& range, T const& value, Compare comp) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::upper_bound(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range)),
					value,
					comp
					),
				sprout::forward<ForwardRange>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		upper_bound(ForwardRange&& range, T const& value) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::upper_bound(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range)),
					value
					),
				sprout::forward<ForwardRange>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename T, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		upper_bound(ForwardRange&& range, T const& value, Compare comp) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::upper_bound(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range)),
					value,
					comp
					),
				sprout::forward<ForwardRange>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_UPPER_BOUND_HPP
