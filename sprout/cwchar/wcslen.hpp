/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CWCHAR_WCSLEN_HPP
#define SPROUT_CWCHAR_WCSLEN_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/cstring/strlen.hpp>

namespace sprout {
	//
	// wcslen
	//
	//	recursion depth:
	//		O(log N)
	//
	inline SPROUT_CONSTEXPR std::size_t
	wcslen(wchar_t const* s) {
		return sprout::strlen(s);
	}
	inline SPROUT_CONSTEXPR std::size_t
	wcslen(wchar_t const* s, std::size_t n) {
		return sprout::strlen(s, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSLEN_HPP
