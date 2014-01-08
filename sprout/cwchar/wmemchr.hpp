/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CWCHAR_WMEMCHR_HPP
#define SPROUT_CWCHAR_WMEMCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/algorithm/find.hpp>

namespace sprout {
	namespace detail {
		inline SPROUT_CONSTEXPR wchar_t const*
		wmemchr_impl(wchar_t const* found, wchar_t const* last) {
			return found == last ? nullptr
				: found
				;
		}
		inline SPROUT_CONSTEXPR wchar_t*
		wmemchr_impl(wchar_t* found, wchar_t* last) {
			return found == last ? nullptr
				: found
				;
		}
	}	// namespace detail

	//
	// wmemchr
	//
	//	recursion depth:
	//		O(log N)
	//
	inline SPROUT_CONSTEXPR wchar_t const*
	wmemchr(wchar_t const* s, wchar_t c, size_t n) {
		return sprout::detail::wmemchr_impl(
			sprout::ptr_unindex(
				sprout::find(
					sprout::ptr_index(s), sprout::ptr_index(s, n),
					c
					)
				),
			s + n
			);
	}

	inline SPROUT_CONSTEXPR wchar_t*
	wmemchr(wchar_t* s, wchar_t c, size_t n) {
		return sprout::detail::wmemchr_impl(
			sprout::ptr_unindex(
				sprout::find(
					sprout::ptr_index(s), sprout::ptr_index(s, n),
					c
					)
				),
			s + n
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WMEMCHR_HPP
