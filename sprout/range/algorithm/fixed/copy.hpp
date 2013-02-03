#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy
			//
			template<typename InputRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy(InputRange const& rng, Result const& result) {
				return sprout::fixed::copy(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename InputRange>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy(InputRange const& rng) {
				return sprout::fixed::copy<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fixed

		using sprout::range::fixed::copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_HPP
