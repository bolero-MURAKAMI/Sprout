#ifndef SPROUT_RANGE_ALGORITHM_STRING_FIT_TO_UPPER_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_STRING_FIT_TO_UPPER_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/string/fit/to_upper_copy.hpp>

namespace sprout {
	namespace range {
		namespace algorithm {
			namespace fit {
				//
				// to_upper_copy
				//
				template<typename InputRange, typename Result>
				inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
				to_upper_copy(InputRange const& rng, Result const& result) {
					return sprout::fit::to_upper_copy(sprout::begin(rng), sprout::end(rng), result);
				}
			}	// namespace fit

			using sprout::range::algorithm::fit::to_upper_copy;
		}	// namespace algorithm

		namespace fit {
			using sprout::range::algorithm::fit::to_upper_copy;
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_STRING_FIT_TO_UPPER_COPY_HPP
