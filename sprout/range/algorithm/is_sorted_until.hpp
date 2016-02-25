/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_IS_SORTED_UNTIL_HPP
#define SPROUT_RANGE_ALGORITHM_IS_SORTED_UNTIL_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/is_sorted_until.hpp>

namespace sprout {
	namespace range {

		// 25.4.1.5 is_sorted
		template<typename ForwardRange>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		is_sorted_until(ForwardRange&& range) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::is_sorted_until(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range))
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}

		template<typename ForwardRange, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		is_sorted_until(ForwardRange&& range, Compare comp) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::is_sorted_until(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					comp
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		is_sorted_until(ForwardRange&& range) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::is_sorted_until(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range))
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		is_sorted_until(ForwardRange&& range, Compare comp) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::is_sorted_until(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					comp
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_SORTED_UNTIL_HPP
