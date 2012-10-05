#ifndef SPROUT_CSTRING_STRCHR_HPP
#define SPROUT_CSTRING_STRCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 7.21.5.2  strchr ä÷êî
	inline SPROUT_CONSTEXPR char const*
	strchr(char const* s, int c) {
		return *s == static_cast<char>(c) ? s
			: !*s ? nullptr
			: sprout::strchr(s + 1, c)
			;
	}

	inline SPROUT_CONSTEXPR char*
	strchr(char* s, int c) {
		return const_cast<char*>(sprout::strchr(const_cast<char const*>(s), c));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRCHR_HPP
