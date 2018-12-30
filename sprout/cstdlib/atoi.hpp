/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDLIB_ATOI_HPP
#define SPROUT_CSTDLIB_ATOI_HPP

#include <sprout/config.hpp>
#include <sprout/cstdlib/ascii_to_int.hpp>

namespace sprout {
	//
	// atoi
	//
	inline SPROUT_CONSTEXPR int
	atoi(char const* str) {
		return sprout::ascii_to_int<int>(str);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR int
	atoi(Char const* str) {
		return sprout::ascii_to_int<int>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_ATOI_HPP
