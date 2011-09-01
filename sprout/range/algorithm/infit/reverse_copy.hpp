#ifndef SPROUT_RANGE_ALGORITHM_INFIT_REVERSE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_INFIT_REVERSE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/infit/reverse_copy.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace infit {
			//
			// reverse_copy
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> reverse_copy(
				Input const& input,
				Result const& result
				)
			{
				return sprout::infit::reverse_copy(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace infit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_INFIT_REVERSE_COPY_HPP
