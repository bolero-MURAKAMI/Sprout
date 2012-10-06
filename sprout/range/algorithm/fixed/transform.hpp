#ifndef SPROUT_RANGE_ALGORITHM_FIXED_TRANSFORM_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_TRANSFORM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/transform.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// transform
			//
			template<typename Input, typename Result, typename UnaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			transform(Input const& input, Result const& result, UnaryOperation op) {
				return sprout::fixed::transform(sprout::begin(input), sprout::end(input), result, op);
			}
			template<typename Input1, typename Input2, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			transform(Input1 const& input1, Input2 const& input2, Result const& result, BinaryOperation op) {
				return sprout::fixed::transform(sprout::begin(input1), sprout::end(input1), sprout::begin(input2), result, op);
			}
		}	// namespace fixed

		using sprout::range::fixed::transform;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_TRANSFORM_HPP
