/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_EQUAL_RANGE_HPP
#define SPROUT_RANGE_ALGORITHM_EQUAL_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/type_traits/lvalue_range.hpp>
#include <sprout/algorithm/equal_range.hpp>

namespace sprout {
	namespace range {
		namespace detail {
			template<typename ForwardRange, typename Pair>
			inline SPROUT_CONSTEXPR typename sprout::range::lvalue_range<ForwardRange>::type
			pair_to_range(Pair const& pair) {
				return {pair.first, pair.second};
			}
		}	// namespace detail


		// 25.4.3.3 equal_range
		template<typename ForwardRange, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::lvalue_range<ForwardRange>::type
		equal_range(ForwardRange&& range, T const& value) {
			return sprout::range::detail::pair_to_range<ForwardRange>(
				sprout::equal_range(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					value
					)
				);
		}

		template<typename ForwardRange, typename T, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::lvalue_range<ForwardRange>::type
		equal_range(ForwardRange&& range, T const& value, Compare comp) {
			return sprout::range::detail::pair_to_range<ForwardRange>(
				sprout::equal_range(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					value,
					comp
					)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_EQUAL_RANGE_HPP
