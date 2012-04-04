#ifndef SPROUT_RANGE_ALGORITHM_FIT_REPLACE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_REPLACE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/replace_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// replace_copy
			//
			template<typename Input, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type replace_copy(
				Input const& input,
				Result const& result,
				T const& old_value,
				T const& new_value
				)
			{
				return sprout::fit::replace_copy(sprout::begin(input), sprout::end(input), result, old_value, new_value);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_REPLACE_COPY_HPP
