#ifndef SPROUT_ALGORITHM_ALL_OF_EQUAL_HPP
#define SPROUT_ALGORITHM_ALL_OF_EQUAL_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	//
	// all_of_equal
	//
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR bool
	all_of_equal(InputIterator first, InputIterator last, T const& value) {
		return first == last ? true
			: *first == value && sprout::all_of_equal(sprout::next(first), last, value)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_ALL_OF_EQUAL_HPP
