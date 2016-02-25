/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIT_REPLACE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_REPLACE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/algorithm/fit/replace_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// replace_copy
			//
			template<typename InputRange, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			replace_copy(InputRange const& rng, Result const& result, T const& old_value, T const& new_value) {
				return sprout::fit::replace_copy(sprout::begin(rng), sprout::end(rng), result, old_value, new_value);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_REPLACE_COPY_HPP
