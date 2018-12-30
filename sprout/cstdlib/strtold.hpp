/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDLIB_STRTOLD_HPP
#define SPROUT_CSTDLIB_STRTOLD_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/cstdlib/str_to_float.hpp>

namespace sprout {
	//
	// strtold
	//
	template<typename Char>
	inline SPROUT_CONSTEXPR long double
	strtold(Char const* str, Char** endptr) {
		return sprout::str_to_float<long double>(str, endptr);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR long double
	strtold(Char const* str, std::nullptr_t) {
		return sprout::str_to_float<long double>(str);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR long double
	strtold(Char const* str) {
		return sprout::str_to_float<long double>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STRTOLD_HPP
