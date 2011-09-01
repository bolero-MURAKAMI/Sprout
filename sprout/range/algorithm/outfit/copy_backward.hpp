#ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_COPY_BACKWARD_HPP
#define SPROUT_RANGE_ALGORITHM_OUTFIT_COPY_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/outfit/copy_backward.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace outfit {
			//
			// copy_backward
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> copy_backward(
				Input const& input,
				Result const& result
				)
			{
				return sprout::outfit::copy_backward(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace outfit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_COPY_BACKWARD_HPP
