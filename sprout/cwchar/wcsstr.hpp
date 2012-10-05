#ifndef SPROUT_CWCHAR_WCSSTR_HPP
#define SPROUT_CWCHAR_WCSSTR_HPP

#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	inline SPROUT_CONSTEXPR wchar_t const*
	wcsstr(wchar_t const* s1, wchar_t const* s2) {
		return !*s2 ? s1
			: !*s1 ? nullptr
			: *s1 == *s2 && sprout::wcsstr(s1 + 1, s2 + 1) ? s1
			: sprout::wcsstr(s1 + 1, s2)
			;
	}

	inline SPROUT_CONSTEXPR wchar_t*
	wcsstr(wchar_t* s1, wchar_t const* s2) {
		return const_cast<wchar_t*>(sprout::wcsstr(const_cast<wchar_t const*>(s1), s2));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSSTR_HPP
