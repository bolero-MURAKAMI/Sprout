/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CWCHAR_WCSNCMP_HPP
#define SPROUT_CWCHAR_WCSNCMP_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/cstring/strncmp.hpp>

namespace sprout {
	//
	// wcsncmp
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR int
	wcsncmp(wchar_t const* s1, wchar_t const* s2, std::size_t n) {
		return sprout::strncmp(s1, s2, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSNCMP_HPP
