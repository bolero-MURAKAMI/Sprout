#ifndef SPROUT_RANGE_ALGORITHM_NONE_OF_EQUAL_HPP
#define SPROUT_RANGE_ALGORITHM_NONE_OF_EQUAL_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/none_of_equal.hpp>

namespace sprout {
	namespace range {
		//
		// none_of_equal
		//
		template<typename InputRange, typename T>
		inline SPROUT_CONSTEXPR bool
		none_of_equal(InputRange const& range, T const& value) {
			return sprout::none_of_equal(sprout::begin(range), sprout::end(range), value);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_NONE_OF_EQUAL_HPP
