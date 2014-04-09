/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_SWAP_RANGES_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_SWAP_RANGES_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/cxx14/swap_ranges.hpp>

namespace sprout {
	namespace range {
		//
		// swap_ranges
		//
		template<typename ForwardRange1, typename ForwardRange2>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange2>::type
		swap_ranges(ForwardRange1&& rng1, ForwardRange2&& rng2) {
			return sprout::range::range_return<ForwardRange2>::pack(
				sprout::swap_ranges(
					sprout::begin(SPROUT_FORWARD(ForwardRange1, rng1)), sprout::end(SPROUT_FORWARD(ForwardRange1, rng1)),
					sprout::begin(SPROUT_FORWARD(ForwardRange2, rng2))
					),
				SPROUT_FORWARD(ForwardRange2, rng2)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange1, typename ForwardRange2>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange2, RetV>::type
		swap_ranges(ForwardRange1&& rng1, ForwardRange2&& rng2) {
			return sprout::range::range_return<ForwardRange2, RetV>::pack(
				sprout::swap_ranges(
					sprout::begin(SPROUT_FORWARD(ForwardRange1, rng1)), sprout::end(SPROUT_FORWARD(ForwardRange1, rng1)),
					sprout::begin(SPROUT_FORWARD(ForwardRange2, rng2))
					),
				SPROUT_FORWARD(ForwardRange2, rng2)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_SWAP_RANGES_HPP
