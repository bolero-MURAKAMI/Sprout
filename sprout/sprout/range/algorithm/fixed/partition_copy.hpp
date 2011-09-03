#ifndef SPROUT_RANGE_ALGORITHM_FIXED_PARTITION_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/partition_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// partition_copy
			//
			template<typename Input, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type partition_copy(
				Input const& input,
				Result const& result,
				Predicate pred
				)
			{
				return sprout::fixed::partition_copy(sprout::begin(input), sprout::end(input), result, pred);
			}
		}	// namespace fixed

		using sprout::range::fixed::partition_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_PARTITION_COPY_HPP
