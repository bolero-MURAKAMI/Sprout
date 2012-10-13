#ifndef SPROUT_ALGORITHM_NONE_OF_EQUAL_HPP
#define SPROUT_ALGORITHM_NONE_OF_EQUAL_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	//
	// none_of_equal
	//
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR bool
	none_of_equal(InputIterator first, InputIterator last, T const& value) {
		return first == last ? true
			: !(*first == value) && sprout::none_of_equal(sprout::next(first), last, value)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_NONE_OF_EQUAL_HPP
