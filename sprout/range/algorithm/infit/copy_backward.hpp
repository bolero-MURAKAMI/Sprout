#ifndef SPROUT_RANGE_ALGORITHM_INFIT_COPY_BACKWARD_HPP
#define SPROUT_RANGE_ALGORITHM_INFIT_COPY_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/infit/copy_backward.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace infit {
			//
			// copy_backward
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> copy_backward(
				Input const& input,
				Result const& result
				)
			{
				return sprout::infit::copy_backward(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace infit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_INFIT_COPY_BACKWARD_HPP
