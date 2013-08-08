/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_MEMCMP_HPP
#define SPROUT_CSTRING_MEMCMP_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>

namespace sprout {
	// 7.21.4.1 memcmp ä÷êî
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
#if 0
	inline SPROUT_CONSTEXPR int
	memcmp(void const* s1, void const* s2, std::size_t n) {
		return sprout::tristate_lexicographical_compare(
			sprout::ptr_index(static_cast<unsigned char const*>(s1)), sprout::ptr_index(static_cast<unsigned char const*>(s1), n),
			sprout::ptr_index(static_cast<unsigned char const*>(s2)), sprout::ptr_index(static_cast<unsigned char const*>(s2), n)
			);
	}
#endif
	template<
		typename T,
		typename sprout::enabler_if<std::is_convertible<T, void const*>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR int
	memcmp(T s1, T s2, std::size_t n) {
		return sprout::tristate_lexicographical_compare(
			sprout::ptr_index(static_cast<unsigned char const*>(s1)), sprout::ptr_index(static_cast<unsigned char const*>(s1), n),
			sprout::ptr_index(static_cast<unsigned char const*>(s2)), sprout::ptr_index(static_cast<unsigned char const*>(s2), n)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_MEMCMP_HPP
