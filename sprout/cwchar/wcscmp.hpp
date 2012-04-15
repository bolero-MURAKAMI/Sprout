#ifndef SPROUT_CWCHAR_WCSCMP_HPP
#define SPROUT_CWCHAR_WCSCMP_HPP

#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	inline SPROUT_CONSTEXPR int wcscmp(wchar_t const* s1, wchar_t const* s2) {
		return !*s1 && !*s2 ? 0
			: !*s1 ? -1
			: !*s2 ? 1
			: *s1 == *s2 ? sprout::wcscmp(s1 + 1, s2 + 1)
			: static_cast<unsigned wchar_t>(*s1) - static_cast<unsigned wchar_t>(*s2)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSCMP_HPP
