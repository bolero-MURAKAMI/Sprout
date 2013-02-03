#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_BACKWARD_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy_backward.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy_backward
			//
			template<typename BidirectionalRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_backward(BidirectionalRange const& rng, Result const& result) {
				return sprout::fixed::copy_backward(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename BidirectionalRange>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_backward(BidirectionalRange const& rng) {
				return sprout::fixed::copy_backward<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fixed

		using sprout::range::fixed::copy_backward;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_BACKWARD_HPP
