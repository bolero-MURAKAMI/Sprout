#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type copy(
				Input const& input,
				Result const& result
				)
			{
				return sprout::fixed::copy(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fixed
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_HPP
