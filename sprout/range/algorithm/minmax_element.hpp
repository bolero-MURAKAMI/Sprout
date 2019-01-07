/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
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
					sprout::range::range_return<ForwardRange>::pack(pair.first, SPROUT_FORWARD(ForwardRange, range)),
					sprout::range::range_return<ForwardRange>::pack(pair.second, SPROUT_FORWARD(ForwardRange, range))
					};
			}

			template<sprout::range::range_return_value RetV, typename ForwardRange, typename Pair>
			inline SPROUT_CONSTEXPR sprout::pair<
				typename sprout::range::range_return<ForwardRange, RetV>::type,
				typename sprout::range::range_return<ForwardRange, RetV>::type
			>
			pack_pair(Pair const& pair, ForwardRange&& range) {
				return {
					sprout::range::range_return<ForwardRange, RetV>::pack(pair.first, SPROUT_FORWARD(ForwardRange, range)),
					sprout::range::range_return<ForwardRange, RetV>::pack(pair.second, SPROUT_FORWARD(ForwardRange, range))
					};
			}
		}	// namespace detail


		// 25.4.7 Minimum and maximum
		template<typename ForwardRange>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::range_return<ForwardRange>::type,
			typename sprout::range::range_return<ForwardRange>::type
		>
		minmax_element(ForwardRange&& range) {
			return sprout::range::detail::pack_pair<ForwardRange>(
				sprout::minmax_element(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range))
					),
				SPROUT_FORWARD(ForwardRange, range)
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
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					comp
					),
				SPROUT_FORWARD(ForwardRange, range)
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
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range))
					),
				SPROUT_FORWARD(ForwardRange, range)
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
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					comp
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_MINMAX_ELEMENT_HPP
