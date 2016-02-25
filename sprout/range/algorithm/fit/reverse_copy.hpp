/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIT_REVERSE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_REVERSE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/algorithm/fit/reverse_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// reverse_copy
			//
			template<typename BidirectionalRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			reverse_copy(BidirectionalRange const& rng, Result const& result) {
				return sprout::fit::reverse_copy(sprout::begin(rng), sprout::end(rng), result);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_REVERSE_COPY_HPP
