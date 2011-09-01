#ifndef SPROUT_RANGE_ALGORITHM_INFIT_COPY_IF_HPP
#define SPROUT_RANGE_ALGORITHM_INFIT_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/infit/copy_if.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace infit {
			//
			// copy_if
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> copy_if(
				Input const& input,
				Result const& result
				)
			{
				return sprout::infit::copy_if(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace infit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_INFIT_COPY_IF_HPP
