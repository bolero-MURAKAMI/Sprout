#ifndef SPROUT_CWCHAR_WCSPBRK_HPP
#define SPROUT_CWCHAR_WCSPBRK_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cwchar/wcschr.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	//
	// wcspbrk
	//
	inline SPROUT_CONSTEXPR wchar_t const*
	wcspbrk(wchar_t const* s1, wchar_t const* s2) {
		return !*s1 ? nullptr
			: sprout::wcschr(s2, *s1) ? s1
			: sprout::wcspbrk(s1 + 1, s2)
			;
	}

	inline SPROUT_CONSTEXPR wchar_t*
	wcspbrk(wchar_t* s1, wchar_t const* s2) {
		return const_cast<wchar_t*>(sprout::wcspbrk(const_cast<wchar_t const*>(s1), s2));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSPBRK_HPP
