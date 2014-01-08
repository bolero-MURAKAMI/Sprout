/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIT_TRANSFORM_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_TRANSFORM_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/algorithm/fit/transform.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// transform
			//
			template<typename InputRange, typename Result, typename UnaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			transform(InputRange const& rng, Result const& result, UnaryOperation op) {
				return sprout::fit::transform(sprout::begin(rng), sprout::end(rng), result, op);
			}
			template<typename InputRange1, typename InputRange2, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			transform(InputRange1 const& rng1, InputRange2 const& rng2, Result const& result, BinaryOperation op) {
				return sprout::fit::transform(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), result, op);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_TRANSFORM_HPP
