#ifndef SPROUT_RANGE_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/swap_element_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// swap_element_copy
			//
			template<typename ForwardRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			swap_element_copy(
				ForwardRange const& rng, Result const& result,
				typename sprout::container_traits<ForwardRange>::const_iterator pos1,
				typename sprout::container_traits<ForwardRange>::const_iterator pos2
				)
			{
				return sprout::fit::swap_element_copy(sprout::begin(rng), sprout::end(rng), result, pos1, pos2);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP
