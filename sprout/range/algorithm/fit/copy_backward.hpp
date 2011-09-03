#ifndef SPROUT_RANGE_ALGORITHM_FIT_COPY_BACKWARD_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_COPY_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/copy_backward.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// copy_backward
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type copy_backward(
				Input const& input,
				Result const& result
				)
			{
				return sprout::fit::copy_backward(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_COPY_BACKWARD_HPP
