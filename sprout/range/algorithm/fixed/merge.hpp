/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIXED_MERGE_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_MERGE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/merge.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// merge
			//
			template<
				typename InputRange1, typename InputRange2, typename Result, typename Compare,
				typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			merge(InputRange1 const& rng1, InputRange2 const& rng2, Result const& result, Compare comp) {
				return sprout::fixed::merge(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2), result, comp);
			}
			template<
				typename InputRange1, typename InputRange2, typename Result,
				typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			merge(InputRange1 const& rng1, InputRange2 const& rng2, Result const& result) {
				return sprout::fixed::merge(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2), result);
			}

			template<typename Result, typename InputRange1, typename InputRange2, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			merge(InputRange1 const& rng1, InputRange2 const& rng2, Compare comp) {
				return sprout::fixed::merge<Result>(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2), comp);
			}
			template<typename Result, typename InputRange1, typename InputRange2>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			merge(InputRange1 const& rng1, InputRange2 const& rng2) {
				return sprout::fixed::merge<Result>(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2));
			}
		}	// namespace fixed

		using sprout::range::fixed::merge;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_MERGE_HPP
