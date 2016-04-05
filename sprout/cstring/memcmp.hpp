/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_MEMCMP_HPP
#define SPROUT_CSTRING_MEMCMP_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>

namespace sprout {
	namespace detail {
		template<typename PtrIterator>
		inline SPROUT_CONSTEXPR int
		memcmp(PtrIterator s1, PtrIterator s2, std::size_t n) {
			return sprout::tristate_lexicographical_compare(
				sprout::ptr_index(s1), sprout::ptr_index(s1, n),
				sprout::ptr_index(s2), sprout::ptr_index(s2, n)
				);
		}
	}	// namespace detail

	// 7.21.4.1 memcmp function
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
#if 0
	inline SPROUT_CONSTEXPR int
	memcmp(void const* s1, void const* s2, std::size_t n) {
		return sprout::detail::memcmp(static_cast<unsigned char const*>(s1), static_cast<unsigned char const*>(s2), n);
	}
#endif
	template<
		typename T,
		typename sprout::enabler_if<std::is_convertible<T, void const*>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR int
	memcmp(T s1, T s2, std::size_t n) {
		return sprout::detail::memcmp(static_cast<unsigned char const*>(s1), static_cast<unsigned char const*>(s2), n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_MEMCMP_HPP
