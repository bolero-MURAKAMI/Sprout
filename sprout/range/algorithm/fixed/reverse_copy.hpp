#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/reverse_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// reverse_copy
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type reverse_copy(
				Input const& input,
				Result const& result
				)
			{
				return sprout::fixed::reverse_copy(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fixed
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP
