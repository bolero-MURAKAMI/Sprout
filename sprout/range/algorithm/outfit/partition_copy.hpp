#ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_PARTITION_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_OUTFIT_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/outfit/partition_copy.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace outfit {
			//
			// partition_copy
			//
			template<typename Input, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> partition_copy(
				Input const& input,
				Result const& result,
				Predicate pred
				)
			{
				return sprout::outfit::partition_copy(sprout::begin(input), sprout::end(input), result, pred);
			}
		}	// namespace outfit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_PARTITION_COPY_HPP
