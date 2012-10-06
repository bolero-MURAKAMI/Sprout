#ifndef SPROUT_RANGE_ALGORITHM_FIT_COPY_IF_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/copy_if.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// copy_if
			//
			template<typename Input, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			copy_if(Input const& input, Result const& result, Predicate pred) {
				return sprout::fit::copy_if(sprout::begin(input), sprout::end(input), result, pred);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_COPY_IF_HPP
