#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/replace_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// replace_copy
			//
			template<typename Input, typename Result, typename T>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type replace_copy(
				Input const& input,
				Result const& result,
				T const& old_value,
				T const& new_value
				)
			{
				return sprout::fixed::replace_copy(sprout::begin(input), sprout::end(input), result, old_value, new_value);
			}
		}	// namespace fixed
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_HPP
