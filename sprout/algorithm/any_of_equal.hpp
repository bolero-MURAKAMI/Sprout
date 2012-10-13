#ifndef SPROUT_ALGORITHM_ANY_OF_EQUAL_HPP
#define SPROUT_ALGORITHM_ANY_OF_EQUAL_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	//
	// any_of_equal
	//
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR bool
	any_of_equal(InputIterator first, InputIterator last, T const& value) {
		return first == last ? false
			: *first == value || sprout::any_of_equal(sprout::next(first), last, value)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_ANY_OF_EQUAL_HPP
