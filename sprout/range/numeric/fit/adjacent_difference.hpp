#ifndef SPROUT_RANGE_NUMERIC_FIT_ADJACENT_DIFFERENCE_HPP
#define SPROUT_RANGE_NUMERIC_FIT_ADJACENT_DIFFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/numeric/fit/adjacent_difference.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// adjacent_difference
			//
			template<typename InputRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			adjacent_difference(InputRange const& rng, Result const& result) {
				return sprout::fit::adjacent_difference(sprout::begin(rng), sprout::end(rng), result);
			}
			template<typename InputRange, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			adjacent_difference(InputRange const& rng, Result const& result, BinaryOperation binary_op) {
				return sprout::fit::adjacent_difference(sprout::begin(rng), sprout::end(rng), result, binary_op);
			}

			template<typename Result, typename InputRange>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			adjacent_difference(InputRange const& rng) {
				return sprout::fit::adjacent_difference<Result>(sprout::begin(rng), sprout::end(rng));
			}
			template<typename Result, typename InputRange, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			adjacent_difference(InputRange const& rng, BinaryOperation binary_op) {
				return sprout::fit::adjacent_difference<Result>(sprout::begin(rng), sprout::end(rng), binary_op);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_FIT_ADJACENT_DIFFERENCE_HPP
