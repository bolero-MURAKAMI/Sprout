#ifndef SPROUT_CWCHAR_WCSRCHR_HPP
#define SPROUT_CWCHAR_WCSRCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	inline SPROUT_CONSTEXPR wchar_t const* wcsrchr(wchar_t const* s, int c) {
		return *s == static_cast<wchar_t>(c) && (!*s || !sprout::wcsrchr(s + 1, c))? s
			: !*s ? nullptr
			: sprout::wcsrchr(s + 1, c)
			;
	}

	inline SPROUT_CONSTEXPR wchar_t* wcsrchr(wchar_t* s, int c) {
		return const_cast<wchar_t*>(sprout::wcsrchr(const_cast<wchar_t const*>(s), c));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSRCHR_HPP
