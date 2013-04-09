#ifndef SPROUT_RANGE_ALGORITHM_FIXED_PARTITION_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/partition_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// partition_copy
			//
			template<typename InputRange, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partition_copy(InputRange const& rng, Result const& result, Predicate pred) {
				return sprout::fixed::partition_copy(sprout::begin(rng), sprout::end(rng), result, pred);
			}

			template<typename Result, typename InputRange, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partition_copy(InputRange const& rng, Predicate pred) {
				return sprout::fixed::partition_copy<Result>(sprout::begin(rng), sprout::end(rng), pred);
			}
		}	// namespace fixed

		using sprout::range::fixed::partition_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_PARTITION_COPY_HPP
