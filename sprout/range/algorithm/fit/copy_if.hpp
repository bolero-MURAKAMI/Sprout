/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIT_COPY_IF_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/algorithm/fit/copy_if.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// copy_if
			//
			template<typename InputRange, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			copy_if(InputRange const& rng, Result const& result, Predicate pred) {
				return sprout::fit::copy_if(sprout::begin(rng), sprout::end(rng), result, pred);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_COPY_IF_HPP
