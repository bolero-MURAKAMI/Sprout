/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_STRING_FIXED_TO_UPPER_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_STRING_FIXED_TO_UPPER_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/string/fixed/to_upper_copy.hpp>

namespace sprout {
	namespace range {
		namespace algorithm {
			namespace fixed {
				//
				// to_upper_copy
				//
				template<typename InputRange, typename Result>
				inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
				to_upper_copy(InputRange const& rng, Result const& result) {
					return sprout::algorithm::fixed::to_upper_copy(sprout::begin(rng), sprout::end(rng), result);
				}

				template<typename Result, typename InputRange>
				inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
				to_upper_copy(InputRange const& rng) {
					return sprout::algorithm::fixed::to_upper_copy<Result>(sprout::begin(rng), sprout::end(rng));
				}
			}	// namespace fixed

			using sprout::range::algorithm::fixed::to_upper_copy;
		}	// namespace algorithm

		namespace fixed {
			using sprout::range::algorithm::fixed::to_upper_copy;
		}	// namespace fixed

		using sprout::range::algorithm::fixed::to_upper_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_STRING_FIXED_TO_UPPER_COPY_HPP
