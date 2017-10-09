/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_FIT_INCLUSIVE_SCAN_HPP
#define SPROUT_RANGE_NUMERIC_FIT_INCLUSIVE_SCAN_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/numeric/fit/inclusive_scan.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// inclusive_scan
			//
			template<typename InputRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			inclusive_scan(InputRange const& rng, Result const& result) {
				return sprout::fit::inclusive_scan(sprout::begin(rng), sprout::end(rng), result);
			}
			template<typename InputRange, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			inclusive_scan(InputRange const& rng, Result const& result, BinaryOperation binary_op) {
				return sprout::fit::inclusive_scan(sprout::begin(rng), sprout::end(rng), result, binary_op);
			}
			template<typename InputRange, typename Result, typename BinaryOperation, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			inclusive_scan(InputRange const& rng, Result const& result, BinaryOperation binary_op, T init) {
				return sprout::fit::inclusive_scan(sprout::begin(rng), sprout::end(rng), result, binary_op, init);
			}

			template<typename Result, typename InputRange>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			inclusive_scan(InputRange const& rng) {
				return sprout::fit::inclusive_scan<Result>(sprout::begin(rng), sprout::end(rng));
			}
			template<typename Result, typename InputRange, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			inclusive_scan(InputRange const& rng, BinaryOperation binary_op) {
				return sprout::fit::inclusive_scan<Result>(sprout::begin(rng), sprout::end(rng), binary_op);
			}
			template<typename Result, typename InputRange, typename BinaryOperation, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			inclusive_scan(InputRange const& rng, BinaryOperation binary_op, T init) {
				return sprout::fit::inclusive_scan<Result>(sprout::begin(rng), sprout::end(rng), binary_op, init);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_FIT_INCLUSIVE_SCAN_HPP
