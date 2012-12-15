#ifndef SPROUT_ALGORITHM_BINARY_SEARCH_HPP
#define SPROUT_ALGORITHM_BINARY_SEARCH_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/lower_bound.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename ForwardIterator, typename T, typename Compare>
		inline SPROUT_CONSTEXPR bool
		binary_search_impl(ForwardIterator first, ForwardIterator last, T const& value, Compare comp) {
			return (first != last && !comp(value, *first));
		}
	}	// namespace detail

	// 25.4.3.4 binary_search
	//
	//	recursion depth:
	//		[first, last) is RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename ForwardIterator, typename T, typename Compare>
	inline SPROUT_CONSTEXPR bool
	binary_search(ForwardIterator first, ForwardIterator last, T const& value, Compare comp) {
		return sprout::detail::binary_search_impl(sprout::lower_bound(first, last, value), last, value, comp);
	}

	template<typename ForwardIterator, typename T>
	inline SPROUT_CONSTEXPR bool
	binary_search(ForwardIterator first, ForwardIterator last, T const& value) {
		return sprout::binary_search(
			first, last, value,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_BINARY_SEARCH_HPP
