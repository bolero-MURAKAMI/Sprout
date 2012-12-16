#ifndef SPROUT_ALGORITHM_ONE_OF_EQUAL_HPP
#define SPROUT_ALGORITHM_ONE_OF_EQUAL_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/none_of_equal.hpp>
#include <sprout/algorithm/find.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR bool
		one_of_equal_impl(InputIterator found, InputIterator last, T const& value) {
			return found != last
				&& sprout::none_of_equal(sprout::next(found), last, value)
				;
		}
	}	// namespace detail

	//
	// one_of_equal
	//
	//	recursion depth:
	//		[first, last) is RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR bool
	one_of_equal(InputIterator first, InputIterator last, T const& value) {
		return sprout::detail::one_of_equal_impl(
			sprout::find(first, last, value), last,
			value
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_ONE_OF_EQUAL_HPP
