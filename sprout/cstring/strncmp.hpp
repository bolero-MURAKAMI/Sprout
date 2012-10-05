#ifndef SPROUT_CSTRING_STRNCMP_HPP
#define SPROUT_CSTRING_STRNCMP_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 7.21.4.4  strncmp ä÷êî
	inline SPROUT_CONSTEXPR int
	strncmp(char const* s1, char const* s2, std::size_t n) {
		return !n || (!*s1 && !*s2) ? 0
			: !*s1 ? -1
			: !*s2 ? 1
			: *s1 == *s2 ? sprout::strncmp(s1 + 1, s2 + 1, n - 1)
			: static_cast<unsigned char>(*s1) - static_cast<unsigned char>(*s2)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRNCMP_HPP
