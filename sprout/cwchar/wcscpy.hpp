/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_WCSCPY_HPP
#define SPROUT_CSTRING_WCSCPY_HPP

#include <sprout/config.hpp>
#include <sprout/cstring/strcpy.hpp>

namespace sprout {

	// 7.24.4.2.1 The wcscpy function
	//
	inline SPROUT_CXX14_CONSTEXPR wchar_t*
	wcscpy(wchar_t* s1, wchar_t const* s2) {
		return sprout::strcpy(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_WCSCPY_HPP
