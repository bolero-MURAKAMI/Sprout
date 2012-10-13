#ifndef SPROUT_RANGE_ALGORITHM_IS_STRICTLY_INCREASING_HPP
#define SPROUT_RANGE_ALGORITHM_IS_STRICTLY_INCREASING_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_strictly_increasing.hpp>

namespace sprout {
	namespace range {
		//
		// is_strictly_increasing
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR bool
		is_strictly_increasing(Range const& range) {
			return sprout::is_strictly_increasing(sprout::begin(range), sprout::end(range));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_STRICTLY_INCREASING_HPP
