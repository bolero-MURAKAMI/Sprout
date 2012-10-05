#ifndef SPROUT_RANGE_ALGORITHM_MINMAX_ELEMENT_HPP
#define SPROUT_RANGE_ALGORITHM_MINMAX_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/minmax_element.hpp>

namespace sprout {
	namespace range {
		namespace detail {
			template<typename Range, typename Pair>
			inline SPROUT_CONSTEXPR sprout::pair<
				typename sprout::range::range_return<Range>::type,
				typename sprout::range::range_return<Range>::type
			>
			pack_pair(Pair const& pair, Range&& range) {
				return {
					sprout::range::range_return<Range>::pack(pair.first, sprout::forward<Range>(range)),
					sprout::range::range_return<Range>::pack(pair.second, sprout::forward<Range>(range))
					};
			}

			template<sprout::range::range_return_value RetV, typename Range, typename Pair>
			inline SPROUT_CONSTEXPR sprout::pair<
				typename sprout::range::range_return<Range, RetV>::type,
				typename sprout::range::range_return<Range, RetV>::type
			>
			pack_pair(Pair const& pair, Range&& range) {
				return {
					sprout::range::range_return<Range, RetV>::pack(pair.first, sprout::forward<Range>(range)),
					sprout::range::range_return<Range, RetV>::pack(pair.second, sprout::forward<Range>(range))
					};
			}
		}	// namespace detail

		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.4.7 Minimum and maximum
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::range_return<Range>::type,
			typename sprout::range::range_return<Range>::type
		>
		minmax_element(Range&& range) {
			return sprout::range::detail::pack_pair<Range>(
				sprout::minmax_element(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range))
					),
				sprout::forward<Range>(range)
				);
		}

		template<typename Range, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::range_return<Range>::type,
			typename sprout::range::range_return<Range>::type
		>
		minmax_element(Range&& range, Compare comp) {
			return sprout::range::detail::pack_pair<Range>(
				sprout::minmax_element(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					comp
					),
				sprout::forward<Range>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::range_return<Range, RetV>::type,
			typename sprout::range::range_return<Range, RetV>::type
		>
		minmax_element(Range&& range) {
			return sprout::range::detail::pack_pair<RetV, Range>(
				sprout::minmax_element(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range))
					),
				sprout::forward<Range>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename Range, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::range_return<Range, RetV>::type,
			typename sprout::range::range_return<Range, RetV>::type
		>
		minmax_element(Range&& range, Compare comp) {
			return sprout::range::detail::pack_pair<RetV, Range>(
				sprout::minmax_element(
					sprout::begin(sprout::forward<Range>(range)),
					sprout::end(sprout::forward<Range>(range)),
					comp
					),
				sprout::forward<Range>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_MINMAX_ELEMENT_HPP
