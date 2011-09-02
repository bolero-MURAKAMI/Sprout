#ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_TRANSFORM_HPP
#define SPROUT_RANGE_ALGORITHM_OUTFIT_TRANSFORM_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/outfit/transform.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace outfit {
			//
			// transform
			//
			template<typename Input, typename Result, typename UnaryOperation>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> transform(
				Input const& input,
				Result const& result,
				UnaryOperation op
				)
			{
				return sprout::outfit::transform(sprout::begin(input), sprout::end(input), result, op);
			}

			//
			// transform
			//
			template<typename Input1, typename Input2, typename Result, typename BinaryOperation>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> transform(
				Input1 const& input1,
				Input2 const& input2,
				Result const& result,
				BinaryOperation op
				)
			{
				return sprout::outfit::transform(sprout::begin(input1), sprout::end(input1), sprout::begin(input2), result, op);
			}
		}	// namespace outfit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_TRANSFORM_HPP
