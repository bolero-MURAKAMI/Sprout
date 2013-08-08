/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CINTTYPES_STRTOIMAX_HPP
#define SPROUT_CINTTYPES_STRTOIMAX_HPP

#include <cstddef>
#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/cstdlib/str_to_int.hpp>

namespace sprout {
	//
	// strtoimax
	//
	inline SPROUT_CONSTEXPR std::intmax_t
	strtoimax(char const* str, char** endptr, int base = 10) {
		return sprout::str_to_int<std::intmax_t>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR std::intmax_t
	strtoimax(Char const* str, Char** endptr, int base = 10) {
		return sprout::str_to_int<std::intmax_t>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR std::intmax_t
	strtoimax(Char const* str, std::nullptr_t endptr, int base = 10) {
		return sprout::str_to_int<std::intmax_t>(str, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR std::intmax_t
	strtoimax(Char const* str, int base = 10) {
		return sprout::str_to_int<std::intmax_t>(str, base);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CINTTYPES_STRTOIMAX_HPP
