/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_LOWER_BOUND_HPP
#define SPROUT_RANGE_ALGORITHM_LOWER_BOUND_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/lower_bound.hpp>

namespace sprout {
	namespace range {

		// 25.4.3.1 lower_bound
		template<typename ForwardRange, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		lower_bound(ForwardRange&& range, T const& value) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::lower_bound(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					value
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}

		template<typename ForwardRange, typename T, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		lower_bound(ForwardRange&& range, T const& value, Compare comp) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::lower_bound(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					value,
					comp
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename T>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		lower_bound(ForwardRange&& range, T const& value) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::lower_bound(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					value
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename T, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		lower_bound(ForwardRange&& range, T const& value, Compare comp) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::lower_bound(
					sprout::begin(SPROUT_FORWARD(ForwardRange, range)),
					sprout::end(SPROUT_FORWARD(ForwardRange, range)),
					value,
					comp
					),
				SPROUT_FORWARD(ForwardRange, range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_LOWER_BOUND_HPP
