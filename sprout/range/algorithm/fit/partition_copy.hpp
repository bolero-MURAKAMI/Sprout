#ifndef SPROUT_RANGE_ALGORITHM_FIT_PARTITION_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/partition_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// partition_copy
			//
			template<typename Input, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type partition_copy(
				Input const& input,
				Result const& result,
				Predicate pred
				)
			{
				return sprout::fit::partition_copy(sprout::begin(input), sprout::end(input), result, pred);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_PARTITION_COPY_HPP
