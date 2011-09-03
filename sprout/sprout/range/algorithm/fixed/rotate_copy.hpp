#ifndef SPROUT_RANGE_ALGORITHM_FIXED_ROTATE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_ROTATE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/rotate_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// rotate_copy
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type rotate_copy(
				Input const& input,
				typename sprout::fixed_container_traits<Input>::const_iterator middle,
				Result const& result
				)
			{
				return sprout::fixed::rotate_copy(sprout::begin(input), middle, sprout::end(input), result);
			}
		}	// namespace fixed

		using sprout::range::fixed::rotate_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_ROTATE_COPY_HPP
