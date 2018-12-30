/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDLIB_STRTOD_HPP
#define SPROUT_CSTDLIB_STRTOD_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/cstdlib/str_to_float.hpp>

namespace sprout {
	//
	// strtod
	//
	template<typename Char>
	inline SPROUT_CONSTEXPR double
	strtod(Char const* str, Char** endptr) {
		return sprout::str_to_float<double>(str, endptr);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR double
	strtod(Char const* str, std::nullptr_t) {
		return sprout::str_to_float<double>(str);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR double
	strtod(Char const* str) {
		return sprout::str_to_float<double>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STRTOD_HPP
