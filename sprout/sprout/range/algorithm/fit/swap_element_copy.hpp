#ifndef SPROUT_RANGE_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/swap_element_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// swap_element_copy
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type swap_element_copy(
				Input const& input,
				Result const& result,
				typename sprout::fixed_container_traits<Input>::const_iterator pos1,
				typename sprout::fixed_container_traits<Input>::const_iterator pos2
				)
			{
				return sprout::fit::swap_element_copy(sprout::begin(input), sprout::end(input), result, pos1, pos2);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP
