/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_WCSNCAT_HPP
#define SPROUT_CSTRING_WCSNCAT_HPP

#include <sprout/config.hpp>
#include <sprout/cstring/strncat.hpp>

namespace sprout {

	// 7.24.4.3.2 The wcsncat function
	//
	inline SPROUT_CXX14_CONSTEXPR wchar_t*
	wcsncat(wchar_t* s1, wchar_t const* s2, std::size_t n) {
		return sprout::strncat(s1, s2, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_WCSNCAT_HPP
