/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDLIB_ATOF_HPP
#define SPROUT_CSTDLIB_ATOF_HPP

#include <sprout/config.hpp>
#include <sprout/cstdlib/str_to_float.hpp>

namespace sprout {
	//
	// atof
	//
	template<typename Char>
	inline SPROUT_CONSTEXPR double
	atof(Char const* str) {
		return sprout::str_to_float<double>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_ATOF_HPP
