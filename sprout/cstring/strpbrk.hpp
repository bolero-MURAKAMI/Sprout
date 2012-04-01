#ifndef SPROUT_CSTRING_STRPBRK_HPP
#define SPROUT_CSTRING_STRPBRK_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strchr.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 7.21.5.4  strpbrk ä÷êî
	inline SPROUT_CONSTEXPR char const* strpbrk(char const* s1, char const* s2) {
		return !*s1 ? nullptr
			: sprout::strchr(s2, *s1) ? s1
			: sprout::strpbrk(s1 + 1, s2)
			;
	}

	inline SPROUT_CONSTEXPR char* strpbrk(char* s1, char const* s2) {
		return const_cast<char*>(sprout::strpbrk(const_cast<char const*>(s1), s2));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRPBRK_HPP
