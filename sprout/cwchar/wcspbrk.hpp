/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CWCHAR_WCSPBRK_HPP
#define SPROUT_CWCHAR_WCSPBRK_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/cstring/strpbrk.hpp>

namespace sprout {
	//
	// wcspbrk
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR wchar_t const*
	wcspbrk(wchar_t const* s1, wchar_t const* s2) {
		return sprout::strpbrk(s1, s2);
	}
	inline SPROUT_CONSTEXPR wchar_t*
	wcspbrk(wchar_t* s1, wchar_t const* s2) {
		return sprout::strpbrk(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSPBRK_HPP
