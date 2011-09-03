#ifndef SPROUT_RANGE_ALGORITHM_FIT_REMOVE_COPY_IF_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_REMOVE_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/remove_copy_if.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// remove_copy_if
			//
			template<typename Input, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type remove_copy_if(
				Input const& input,
				Result const& result,
				Predicate pred
				)
			{
				return sprout::fit::remove_copy_if(sprout::begin(input), sprout::end(input), result, pred);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_REMOVE_COPY_IF_HPP
