#ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_SET_SYMMETRIC_DIFFERENCE_HPP
#define SPROUT_RANGE_ALGORITHM_OUTFIT_SET_SYMMETRIC_DIFFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/outfit/set_symmetric_difference.hpp>

namespace sprout {
	namespace range {
		namespace outfit {
			//
			// set_symmetric_difference
			//
			template<typename Input1, typename Input2, typename Result, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type set_symmetric_difference(
				Input1 const& input1,
				Input2 const& input2,
				Result const& result,
				Compare comp
				)
			{
				return sprout::outfit::set_symmetric_difference(sprout::begin(input1), sprout::end(input1), sprout::begin(input2), sprout::end(input2), result, comp);
			}

			//
			// set_symmetric_difference
			//
			template<typename Input1, typename Input2, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type set_symmetric_difference(
				Input1 const& input1,
				Input2 const& input2,
				Result const& result
				)
			{
				return sprout::outfit::set_symmetric_difference(sprout::begin(input1), sprout::end(input1), sprout::begin(input2), sprout::end(input2), result);
			}
		}	// namespace outfit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_SET_SYMMETRIC_DIFFERENCE_HPP
