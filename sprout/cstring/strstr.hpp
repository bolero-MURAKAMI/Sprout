#ifndef SPROUT_CSTRING_STRSTR_HPP
#define SPROUT_CSTRING_STRSTR_HPP

#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 7.21.5.7  strstr ä÷êî
	inline SPROUT_CONSTEXPR char const*
	strstr(char const* s1, char const* s2) {
		return !*s2 ? s1
			: !*s1 ? nullptr
			: *s1 == *s2 && sprout::strstr(s1 + 1, s2 + 1) ? s1
			: sprout::strstr(s1 + 1, s2)
			;
	}

	inline SPROUT_CONSTEXPR char*
	strstr(char* s1, char const* s2) {
		return const_cast<char*>(sprout::strstr(const_cast<char const*>(s1), s2));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRSTR_HPP
