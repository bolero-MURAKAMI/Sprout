#ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_REPLACE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_OUTFIT_REPLACE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/outfit/replace_copy.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace outfit {
			//
			// replace_copy
			//
			template<typename Input, typename Result, typename T>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> replace_copy(
				Input const& input,
				Result const& result,
				T const& old_value,
				T const& new_value
				)
			{
				return sprout::outfit::replace_copy(sprout::begin(input), sprout::end(input), result, old_value, new_value);
			}
		}	// namespace outfit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_REPLACE_COPY_HPP
