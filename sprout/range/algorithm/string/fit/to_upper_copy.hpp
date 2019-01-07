/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_STRING_FIT_TO_UPPER_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_STRING_FIT_TO_UPPER_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/algorithm/string/fit/to_upper_copy.hpp>

namespace sprout {
	namespace range {
		namespace algorithm {
			namespace fit {
				//
				// to_upper_copy
				//
				template<typename InputRange, typename Result>
				inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
				to_upper_copy(InputRange const& rng, Result const& result) {
					return sprout::fit::to_upper_copy(sprout::begin(rng), sprout::end(rng), result);
				}
			}	// namespace fit

			using sprout::range::algorithm::fit::to_upper_copy;
		}	// namespace algorithm

		namespace fit {
			using sprout::range::algorithm::fit::to_upper_copy;
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_STRING_FIT_TO_UPPER_COPY_HPP
