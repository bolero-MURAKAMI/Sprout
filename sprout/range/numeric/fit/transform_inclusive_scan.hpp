/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_FIT_TRANSFORM_INCLUSIVE_SCAN_HPP
#define SPROUT_RANGE_NUMERIC_FIT_TRANSFORM_INCLUSIVE_SCAN_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/numeric/fit/transform_inclusive_scan.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// transform_inclusive_scan
			//
			template<typename InputRange, typename Result, typename BinaryOperation, typename UnaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			transform_inclusive_scan(InputRange const& rng, Result const& result, BinaryOperation binary_op, UnaryOperation unary_op) {
				return sprout::fit::transform_inclusive_scan(sprout::begin(rng), sprout::end(rng), result, binary_op, unary_op);
			}
			template<typename InputRange, typename Result, typename BinaryOperation, typename UnaryOperation, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			transform_inclusive_scan(InputRange const& rng, Result const& result, BinaryOperation binary_op, UnaryOperation unary_op, T init) {
				return sprout::fit::transform_inclusive_scan(sprout::begin(rng), sprout::end(rng), result, binary_op, unary_op, init);
			}

			template<typename Result, typename InputRange>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			transform_inclusive_scan(InputRange const& rng) {
				return sprout::fit::transform_inclusive_scan<Result>(sprout::begin(rng), sprout::end(rng));
			}
			template<typename Result, typename InputRange, typename BinaryOperation, typename UnaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			transform_inclusive_scan(InputRange const& rng, BinaryOperation binary_op, UnaryOperation unary_op) {
				return sprout::fit::transform_inclusive_scan<Result>(sprout::begin(rng), sprout::end(rng), binary_op, unary_op);
			}
			template<typename Result, typename InputRange, typename BinaryOperation, typename UnaryOperation, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			transform_inclusive_scan(InputRange const& rng, BinaryOperation binary_op, UnaryOperation unary_op, T init) {
				return sprout::fit::transform_inclusive_scan<Result>(sprout::begin(rng), sprout::end(rng), binary_op, unary_op, init);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_FIT_TRANSFORM_INCLUSIVE_SCAN_HPP
