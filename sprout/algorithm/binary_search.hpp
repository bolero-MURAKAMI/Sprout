/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_BINARY_SEARCH_HPP
#define SPROUT_ALGORITHM_BINARY_SEARCH_HPP

#include <iterator>
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
	//		O(log N)
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
