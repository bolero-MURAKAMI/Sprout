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
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type adjacent_difference(
				Input const& input,
				Result const& result
				)
			{
				return sprout::fit::adjacent_difference(sprout::begin(input), sprout::end(input), result);
			}
			//
			// adjacent_difference
			//
			template<typename Input, typename Result, typename BinaryOperation>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type adjacent_difference(
				Input const& input,
				Result const& result,
				BinaryOperation binary_op
				)
			{
				return sprout::fit::adjacent_difference(sprout::begin(input), sprout::end(input), result, binary_op);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_FIT_ADJACENT_DIFFERENCE_HPP
