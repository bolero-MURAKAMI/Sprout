/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CWCHAR_WMEMCMP_HPP
#define SPROUT_CWCHAR_WMEMCMP_HPP

#include <sprout/config.hpp>
#include <sprout/cstring/memcmp.hpp>

namespace sprout {
	//
	// wmemcmp
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR int
	wmemcmp(wchar_t const* s1, wchar_t const* s2, std::size_t n) {
		return sprout::detail::memcmp(s1, s2, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WMEMCMP_HPP
