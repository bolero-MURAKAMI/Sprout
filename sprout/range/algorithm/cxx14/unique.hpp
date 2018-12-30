/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_UNIQUE_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_UNIQUE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/cxx14/unique.hpp>

namespace sprout {
	namespace range {
		//
		// unique
		//
		template<typename ForwardRange>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		unique(ForwardRange&& rng) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::unique(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng))),
				SPROUT_FORWARD(ForwardRange, rng)
				);
		}
		template<sprout::range::range_return_value RetV, typename ForwardRange>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		unique(ForwardRange&& rng) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::unique(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng))),
				SPROUT_FORWARD(ForwardRange, rng)
				);
		}

		template<typename ForwardRange, typename BinaryPredicate>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		unique(ForwardRange&& rng, BinaryPredicate pred) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::unique(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng)), pred),
				SPROUT_FORWARD(ForwardRange, rng)
				);
		}
		template<sprout::range::range_return_value RetV, typename ForwardRange, typename BinaryPredicate>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		unique(ForwardRange&& rng, BinaryPredicate pred) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::unique(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng)), pred),
				SPROUT_FORWARD(ForwardRange, rng)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_UNIQUE_HPP
