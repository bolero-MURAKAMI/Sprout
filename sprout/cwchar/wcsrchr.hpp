/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CWCHAR_WCSRCHR_HPP
#define SPROUT_CWCHAR_WCSRCHR_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/cstring/strrchr.hpp>

namespace sprout {
	//
	// wcsrchr
	//
	//	recursion depth:
	//		O(log N)
	//
	inline SPROUT_CONSTEXPR wchar_t const*
	wcsrchr(wchar_t const* s, wchar_t c) {
		return sprout::strrchr(s, c);
	}
	inline SPROUT_CONSTEXPR wchar_t*
	wcsrchr(wchar_t* s, wchar_t c) {
		return sprout::strrchr(s, c);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSRCHR_HPP
