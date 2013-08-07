#ifndef SPROUT_RANGE_ALGORITHM_MINMAX_ELEMENT_HPP
#define SPROUT_RANGE_ALGORITHM_MINMAX_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/minmax_element.hpp>

namespace sprout {
	namespace range {
		namespace detail {
			template<typename ForwardRange, typename Pair>
			inline SPROUT_CONSTEXPR sprout::pair<
				typename sprout::range::range_return<ForwardRange>::type,
				typename sprout::range::range_return<ForwardRange>::type
			>
			pack_pair(Pair const& pair, ForwardRange&& range) {
				return {
					sprout::range::range_return<ForwardRange>::pack(pair.first, sprout::forward<ForwardRange>(range)),
					sprout::range::range_return<ForwardRange>::pack(pair.second, sprout::forward<ForwardRange>(range))
					};
			}

			template<sprout::range::range_return_value RetV, typename ForwardRange, typename Pair>
			inline SPROUT_CONSTEXPR sprout::pair<
				typename sprout::range::range_return<ForwardRange, RetV>::type,
				typename sprout::range::range_return<ForwardRange, RetV>::type
			>
			pack_pair(Pair const& pair, ForwardRange&& range) {
				return {
					sprout::range::range_return<ForwardRange, RetV>::pack(pair.first, sprout::forward<ForwardRange>(range)),
					sprout::range::range_return<ForwardRange, RetV>::pack(pair.second, sprout::forward<ForwardRange>(range))
					};
			}
		}	// namespace detail

		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.4.7 Minimum and maximum
		template<typename ForwardRange>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::range_return<ForwardRange>::type,
			typename sprout::range::range_return<ForwardRange>::type
		>
		minmax_element(ForwardRange&& range) {
			return sprout::range::detail::pack_pair<ForwardRange>(
				sprout::minmax_element(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range))
					),
				sprout::forward<ForwardRange>(range)
				);
		}

		template<typename ForwardRange, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::range_return<ForwardRange>::type,
			typename sprout::range::range_return<ForwardRange>::type
		>
		minmax_element(ForwardRange&& range, Compare comp) {
			return sprout::range::detail::pack_pair<ForwardRange>(
				sprout::minmax_element(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range)),
					comp
					),
				sprout::forward<ForwardRange>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::range_return<ForwardRange, RetV>::type,
			typename sprout::range::range_return<ForwardRange, RetV>::type
		>
		minmax_element(ForwardRange&& range) {
			return sprout::range::detail::pack_pair<RetV, ForwardRange>(
				sprout::minmax_element(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range))
					),
				sprout::forward<ForwardRange>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::range_return<ForwardRange, RetV>::type,
			typename sprout::range::range_return<ForwardRange, RetV>::type
		>
		minmax_element(ForwardRange&& range, Compare comp) {
			return sprout::range::detail::pack_pair<RetV, ForwardRange>(
				sprout::minmax_element(
					sprout::begin(sprout::forward<ForwardRange>(range)),
					sprout::end(sprout::forward<ForwardRange>(range)),
					comp
					),
				sprout::forward<ForwardRange>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_MINMAX_ELEMENT_HPP
