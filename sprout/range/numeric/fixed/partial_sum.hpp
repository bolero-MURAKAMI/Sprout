#ifndef SPROUT_RANGE_NUMERIC_FIXED_PARTIAL_SUM_HPP
#define SPROUT_RANGE_NUMERIC_FIXED_PARTIAL_SUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/numeric/fixed/partial_sum.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// partial_sum
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partial_sum(Input const& input, Result const& result) {
				return sprout::fixed::partial_sum(sprout::begin(input), sprout::end(input), result);
			}
			template<typename Input, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partial_sum(Input const& input, Result const& result, BinaryOperation binary_op) {
				return sprout::fixed::partial_sum(sprout::begin(input), sprout::end(input), result, binary_op);
			}

			template<typename Result, typename Input>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partial_sum(Input const& input) {
				return sprout::fixed::partial_sum<Result>(sprout::begin(input), sprout::end(input));
			}
			template<typename Result, typename Input, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partial_sum(Input const& input, BinaryOperation binary_op) {
				return sprout::fixed::partial_sum<Result>(sprout::begin(input), sprout::end(input), binary_op);
			}
		}	// namespace fixed

		using sprout::range::fixed::partial_sum;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_FIXED_PARTIAL_SUM_HPP
