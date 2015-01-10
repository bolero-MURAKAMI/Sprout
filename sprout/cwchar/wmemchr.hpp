/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CWCHAR_WMEMCHR_HPP
#define SPROUT_CWCHAR_WMEMCHR_HPP

#include <sprout/config.hpp>
#include <sprout/cstring/memchr.hpp>

namespace sprout {
	//
	// wmemchr
	//
	//	recursion depth:
	//		O(log N)
	//
	inline SPROUT_CONSTEXPR wchar_t const*
	wmemchr(wchar_t const* s, wchar_t c, size_t n) {
		return sprout::detail::memchr(s, c, n);
	}

	inline SPROUT_CONSTEXPR wchar_t*
	wmemchr(wchar_t* s, wchar_t c, size_t n) {
		return sprout::detail::memchr(s, c, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WMEMCHR_HPP
