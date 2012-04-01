#ifndef SPROUT_CSTRING_STRCOLL_HPP
#define SPROUT_CSTRING_STRCOLL_HPP

#include <sprout/config.hpp>
#include <sprout/cstring/strcmp.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 7.21.4.3  strcoll ä÷êî
	inline SPROUT_CONSTEXPR int strcoll(char const* s1, char const* s2) {
		return sprout::strcmp(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRCOLL_HPP
