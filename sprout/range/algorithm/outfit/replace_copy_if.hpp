#ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_REPLACE_COPY_IF_HPP
#define SPROUT_RANGE_ALGORITHM_OUTFIT_REPLACE_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/outfit/replace_copy_if.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace outfit {
			//
			// replace_copy_if
			//
			template<typename Input, typename Result, typename T, typename Predicate>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> replace_copy_if(
				Input const& input,
				Result const& result,
				Predicate pred,
				T const& new_value
				)
			{
				return sprout::outfit::replace_copy_if(sprout::begin(input), sprout::end(input), result, pred, new_value);
			}
		}	// namespace outfit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_REPLACE_COPY_IF_HPP
