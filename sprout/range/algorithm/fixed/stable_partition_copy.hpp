#ifndef SPROUT_RANGE_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/stable_partition_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// stable_partition_copy
			//
			template<typename Input, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type stable_partition_copy(
				Input const& input,
				Result const& result,
				Predicate pred
				)
			{
				return sprout::fixed::stable_partition_copy(sprout::begin(input), sprout::end(input), result, pred);
			}
		}	// namespace fixed

		using sprout::range::fixed::stable_partition_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_STABLE_PARTITION_COPY_HPP
