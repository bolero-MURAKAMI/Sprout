#ifndef SPROUT_CWCHAR_WCSCOLL_HPP
#define SPROUT_CWCHAR_WCSCOLL_HPP

#include <sprout/config.hpp>
#include <sprout/cstring/strcmp.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	inline SPROUT_CONSTEXPR int wcscoll(wchar_t const* s1, wchar_t const* s2) {
		return sprout::wcscmp(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSCOLL_HPP
