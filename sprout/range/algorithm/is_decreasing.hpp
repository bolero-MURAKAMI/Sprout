#ifndef SPROUT_RANGE_ALGORITHM_IS_DECREASING_HPP
#define SPROUT_RANGE_ALGORITHM_IS_DECREASING_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_decreasing.hpp>

namespace sprout {
	namespace range {
		//
		// is_decreasing
		//
		template<typename ForwardRange>
		inline SPROUT_CONSTEXPR bool
		is_decreasing(ForwardRange const& range) {
			return sprout::is_decreasing(sprout::begin(range), sprout::end(range));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_DECREASING_HPP
