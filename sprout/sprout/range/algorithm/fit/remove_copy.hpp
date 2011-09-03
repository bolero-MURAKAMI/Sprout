#ifndef SPROUT_RANGE_ALGORITHM_FIT_REMOVE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_REMOVE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/remove_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// remove_copy
			//
			template<typename Input, typename Result, typename T>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type remove_copy(
				Input const& input,
				Result const& result,
				T const& value
				)
			{
				return sprout::fit::remove_copy(sprout::begin(input), sprout::end(input), result, value);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_REMOVE_COPY_HPP
