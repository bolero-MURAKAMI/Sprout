#ifndef SPROUT_RANGE_ALGORITHM_INFIT_ROTATE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_INFIT_ROTATE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/infit/rotate_copy.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace infit {
			//
			// rotate_copy
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> rotate_copy(
				Input const& input,
				typename sprout::fixed_container_traits<Input>::const_iterator middle,
				Result const& result
				)
			{
				return sprout::infit::rotate_copy(sprout::begin(input), middle, sprout::end(input), result);
			}
		}	// namespace infit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_INFIT_ROTATE_COPY_HPP
