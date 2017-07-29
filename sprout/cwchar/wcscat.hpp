/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_WCSCAT_HPP
#define SPROUT_CSTRING_WCSCAT_HPP

#include <sprout/config.hpp>
#include <sprout/cstring/strcat.hpp>

namespace sprout {

	// 7.24.4.3.1 The wcscat function
	//
	inline SPROUT_CXX14_CONSTEXPR wchar_t*
	wcscat(wchar_t* s1, wchar_t const* s2) {
		return sprout::strcat(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_WCSCAT_HPP
