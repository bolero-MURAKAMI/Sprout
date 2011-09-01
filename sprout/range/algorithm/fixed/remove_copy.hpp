#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/remove_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// remove_copy
			//
			template<typename Input, typename Result, typename T>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type remove_copy(
				Input const& input,
				Result const& result,
				T const& value
				)
			{
				return sprout::fixed::remove_copy(sprout::begin(input), sprout::end(input), result, value);
			}
		}	// namespace fixed
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_HPP
