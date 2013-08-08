/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDLIB_STRTOUL_HPP
#define SPROUT_CSTDLIB_STRTOUL_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstdlib/str_to_int.hpp>

namespace sprout {
	//
	// strtoul
	//
	inline SPROUT_CONSTEXPR unsigned long
	strtoul(char const* str, char** endptr, int base = 10) {
		return sprout::str_to_int<unsigned long>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR unsigned long
	strtoul(Char const* str, Char** endptr, int base = 10) {
		return sprout::str_to_int<unsigned long>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR unsigned long
	strtoul(Char const* str, std::nullptr_t, int base = 10) {
		return sprout::str_to_int<unsigned long>(str, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR unsigned long
	strtoul(Char const* str, int base = 10) {
		return sprout::str_to_int<unsigned long>(str, base);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STRTOUL_HPP
