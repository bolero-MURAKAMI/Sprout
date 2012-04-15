#ifndef SPROUT_CWCHAR_WCSCHR_HPP
#define SPROUT_CWCHAR_WCSCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	inline SPROUT_CONSTEXPR wchar_t const* wcschr(wchar_t const* s, int c) {
		return *s == static_cast<wchar_t>(c) ? s
			: !*s ? nullptr
			: sprout::wcschr(s + 1, c)
			;
	}

	inline SPROUT_CONSTEXPR wchar_t* wcschr(wchar_t* s, int c) {
		return const_cast<wchar_t*>(sprout::wcschr(const_cast<wchar_t const*>(s), c));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSCHR_HPP
