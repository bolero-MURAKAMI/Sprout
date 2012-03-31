#ifndef SPROUT_RANGE_ALGORITHM_FIT_UNIQUE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_UNIQUE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/unique_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// unique_copy
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type unique_copy(
				Input const& input,
				Result const& result
				)
			{
				return sprout::fit::unique_copy(sprout::begin(input), sprout::end(input), result);
			}

			//
			// unique_copy
			//
			template<typename Input, typename Result, typename BinaryPredicate>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type unique_copy(
				Input const& input,
				Result const& result,
				BinaryPredicate pred
				)
			{
				return sprout::fit::unique_copy(sprout::begin(input), sprout::end(input), result, pred);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_UNIQUE_COPY_HPP
