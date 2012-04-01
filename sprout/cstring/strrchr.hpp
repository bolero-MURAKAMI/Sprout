#ifndef SPROUT_CSTRING_STRRCHR_HPP
#define SPROUT_CSTRING_STRRCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 7.21.5.5  strrchr ä÷êî
	inline SPROUT_CONSTEXPR char const* strrchr(char const* s, int c) {
		return *s == static_cast<char>(c) && (!*s || !sprout::strrchr(s + 1, c))? s
			: !*s ? nullptr
			: sprout::strrchr(s + 1, c)
			;
	}

	inline SPROUT_CONSTEXPR char* strrchr(char* s, int c) {
		return const_cast<char*>(sprout::strrchr(const_cast<char const*>(s), c));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRRCHR_HPP
