/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CWCHAR_WMEMSET_HPP
#define SPROUT_CWCHAR_WMEMSET_HPP

#include <sprout/config.hpp>
#include <sprout/cstring/memset.hpp>

namespace sprout {

	// 7.24.4.6.2 The wmemset function
	//
	inline SPROUT_CXX14_CONSTEXPR wchar_t*
	wmemset(wchar_t* s, wchar_t c, std::size_t n) {
		return sprout::detail::memset(s, c, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WMEMSET_HPP
