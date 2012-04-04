#ifndef SPROUT_RANGE_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP
#define SPROUT_RANGE_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/numeric/fixed/adjacent_difference.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// adjacent_difference
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type adjacent_difference(
				Input const& input,
				Result const& result
				)
			{
				return sprout::fixed::adjacent_difference(sprout::begin(input), sprout::end(input), result);
			}
			//
			// adjacent_difference
			//
			template<typename Input, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type adjacent_difference(
				Input const& input,
				Result const& result,
				BinaryOperation binary_op
				)
			{
				return sprout::fixed::adjacent_difference(sprout::begin(input), sprout::end(input), result, binary_op);
			}
		}	// namespace fixed

		using sprout::range::fixed::adjacent_difference;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP
