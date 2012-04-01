#ifndef SPROUT_CSTRING_STRCMP_HPP
#define SPROUT_CSTRING_STRCMP_HPP

#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 7.21.4.2  strcmp ä÷êî
	inline SPROUT_CONSTEXPR int strcmp(char const* s1, char const* s2) {
		return !*s1 && !*s2 ? 0
			: !*s1 ? -1
			: !*s2 ? 1
			: *s1 == *s2 ? sprout::strcmp(s1 + 1, s2 + 1)
			: static_cast<unsigned char>(*s1) - static_cast<unsigned char>(*s2)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRCMP_HPP
