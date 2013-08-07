#ifndef SPROUT_RANGE_ALGORITHM_IS_INCREASING_HPP
#define SPROUT_RANGE_ALGORITHM_IS_INCREASING_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_increasing.hpp>

namespace sprout {
	namespace range {
		//
		// is_increasing
		//
		template<typename ForwardRange>
		inline SPROUT_CONSTEXPR bool
		is_increasing(ForwardRange const& range) {
			return sprout::is_increasing(sprout::begin(range), sprout::end(range));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_INCREASING_HPP
