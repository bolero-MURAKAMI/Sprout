#ifndef SPROUT_RANGE_ALGORITHM_FIXED_PARTITION_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/partition_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// partition_copy
			//
			template<typename Input, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partition_copy(Input const& input, Result const& result, Predicate pred) {
				return sprout::fixed::partition_copy(sprout::begin(input), sprout::end(input), result, pred);
			}

			template<typename Result, typename Input, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partition_copy(Input const& input, Predicate pred) {
				return sprout::fixed::partition_copy<Result>(sprout::begin(input), sprout::end(input), pred);
			}
		}	// namespace fixed

		using sprout::range::fixed::partition_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_PARTITION_COPY_HPP
