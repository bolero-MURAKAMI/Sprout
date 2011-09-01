#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_BACKWARD_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/copy_backward.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy_backward
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type copy_backward(
				Input const& input,
				Result const& result
				)
			{
				return sprout::fixed::copy_backward(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fixed
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_BACKWARD_HPP
