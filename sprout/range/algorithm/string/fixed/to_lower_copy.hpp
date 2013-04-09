#ifndef SPROUT_RANGE_ALGORITHM_STRING_FIXED_TO_LOWER_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_STRING_FIXED_TO_LOWER_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/string/fixed/to_lower_copy.hpp>

namespace sprout {
	namespace range {
		namespace algorithm {
			namespace fixed {
				//
				// to_lower_copy
				//
				template<typename InputRange, typename Result>
				inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
				to_lower_copy(InputRange const& rng, Result const& result) {
					return sprout::algorithm::fixed::to_lower_copy(sprout::begin(rng), sprout::end(rng), result);
				}

				template<typename Result, typename InputRange>
				inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
				to_lower_copy(InputRange const& rng) {
					return sprout::algorithm::fixed::to_lower_copy<Result>(sprout::begin(rng), sprout::end(rng));
				}
			}	// namespace fixed

			using sprout::range::algorithm::fixed::to_lower_copy;
		}	// namespace algorithm

		namespace fixed {
			using sprout::range::algorithm::fixed::to_lower_copy;
		}	// namespace fixed

		using sprout::range::algorithm::fixed::to_lower_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_STRING_FIXED_TO_LOWER_COPY_HPP
