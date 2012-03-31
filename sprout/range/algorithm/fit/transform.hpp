#ifndef SPROUT_RANGE_ALGORITHM_FIT_TRANSFORM_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_TRANSFORM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/transform.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// transform
			//
			template<typename Input, typename Result, typename UnaryOperation>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type transform(
				Input const& input,
				Result const& result,
				UnaryOperation op
				)
			{
				return sprout::fit::transform(sprout::begin(input), sprout::end(input), result, op);
			}

			//
			// transform
			//
			template<typename Input1, typename Input2, typename Result, typename BinaryOperation>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type transform(
				Input1 const& input1,
				Input2 const& input2,
				Result const& result,
				BinaryOperation op
				)
			{
				return sprout::fit::transform(sprout::begin(input1), sprout::end(input1), sprout::begin(input2), result, op);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_TRANSFORM_HPP
