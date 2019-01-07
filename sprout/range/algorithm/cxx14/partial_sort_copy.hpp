/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_PARTIAL_SORT_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_PARTIAL_SORT_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/cxx14/partial_sort_copy.hpp>

namespace sprout {
	namespace range {
		//
		// partial_sort_copy
		//
		template<typename InputRange, typename RandomAccessRange, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<RandomAccessRange>::type
		partial_sort_copy(InputRange const& rng1, RandomAccessRange&& rng2, Compare comp) {
			return sprout::range::range_return<RandomAccessRange>::pack(
				sprout::partial_sort_copy(
					sprout::begin(rng1), sprout::end(rng1),
					sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng2)), sprout::end(SPROUT_FORWARD(RandomAccessRange, rng2)),
					comp
					),
				SPROUT_FORWARD(RandomAccessRange, rng2)
				);
		}
		template<sprout::range::range_return_value RetV, typename InputRange, typename RandomAccessRange, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<RandomAccessRange, RetV>::type
		partial_sort_copy(InputRange const& rng1, RandomAccessRange&& rng2, Compare comp) {
			return sprout::range::range_return<RandomAccessRange, RetV>::pack(
				sprout::partial_sort_copy(
					sprout::begin(rng1), sprout::end(rng1),
					sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng2)), sprout::end(SPROUT_FORWARD(RandomAccessRange, rng2)),
					comp
					),
				SPROUT_FORWARD(RandomAccessRange, rng2)
				);
		}

		template<typename InputRange, typename RandomAccessRange>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<RandomAccessRange>::type
		partial_sort_copy(InputRange const& rng1, RandomAccessRange&& rng2) {
			return sprout::range::range_return<RandomAccessRange>::pack(
				sprout::partial_sort_copy(
					sprout::begin(rng1), sprout::end(rng1),
					sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng2)), sprout::end(SPROUT_FORWARD(RandomAccessRange, rng2))
					),
				SPROUT_FORWARD(RandomAccessRange, rng2)
				);
		}
		template<sprout::range::range_return_value RetV, typename InputRange, typename RandomAccessRange>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<RandomAccessRange, RetV>::type
		partial_sort_copy(InputRange const& rng1, RandomAccessRange&& rng2) {
			return sprout::range::range_return<RandomAccessRange, RetV>::pack(
				sprout::partial_sort_copy(
					sprout::begin(rng1), sprout::end(rng1),
					sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng2)), sprout::end(SPROUT_FORWARD(RandomAccessRange, rng2))
					),
				SPROUT_FORWARD(RandomAccessRange, rng2)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_PARTIAL_SORT_COPY_HPP
