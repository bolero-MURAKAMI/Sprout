#ifndef SPROUT_RANGE_ALGORITHM_ALL_OF_EQUAL_HPP
#define SPROUT_RANGE_ALGORITHM_ALL_OF_EQUAL_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/all_of_equal.hpp>

namespace sprout {
	namespace range {
		//
		// all_of_equal
		//
		template<typename InputRange, typename T>
		inline SPROUT_CONSTEXPR bool
		all_of_equal(InputRange const& range, T const& value) {
			return sprout::all_of_equal(sprout::begin(range), sprout::end(range), value);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_ALL_OF_EQUAL_HPP
