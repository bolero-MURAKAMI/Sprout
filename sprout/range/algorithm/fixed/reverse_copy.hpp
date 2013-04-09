#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/reverse_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// reverse_copy
			//
			template<typename BidirectionalRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			reverse_copy(BidirectionalRange const& rng, Result const& result) {
				return sprout::fixed::reverse_copy(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename BidirectionalRange>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			reverse_copy(BidirectionalRange const& rng) {
				return sprout::fixed::reverse_copy<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fixed

		using sprout::range::fixed::reverse_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP
