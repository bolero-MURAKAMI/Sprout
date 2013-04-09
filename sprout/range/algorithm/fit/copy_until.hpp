#ifndef SPROUT_RANGE_ALGORITHM_FIT_COPY_UNTIL_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_COPY_UNTIL_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/copy_until.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// copy_until
			//
			template<typename InputRange, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			copy_until(InputRange const& rng, Result const& result, Predicate pred) {
				return sprout::fit::copy_until(sprout::begin(rng), sprout::end(rng), result, pred);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_COPY_UNTIL_HPP
