#ifndef SPROUT_RANGE_ALGORITHM_FIT_ROTATE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_ROTATE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/rotate_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// rotate_copy
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			rotate_copy(
				Input const& input, typename sprout::container_traits<Input>::const_iterator middle,
				Result const& result
				)
			{
				return sprout::fit::rotate_copy(sprout::begin(input), middle, sprout::end(input), result);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_ROTATE_COPY_HPP
