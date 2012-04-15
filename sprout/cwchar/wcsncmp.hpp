#ifndef SPROUT_CWCHAR_WCSNCMP_HPP
#define SPROUT_CWCHAR_WCSNCMP_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	inline SPROUT_CONSTEXPR int wcsncmp(wchar_t const* s1, wchar_t const* s2, std::size_t n) {
		return !n || (!*s1 && !*s2) ? 0
			: !*s1 ? -1
			: !*s2 ? 1
			: *s1 == *s2 ? sprout::wcsncmp(s1 + 1, s2 + 1, n - 1)
			: static_cast<unsigned wchar_t>(*s1) - static_cast<unsigned wchar_t>(*s2)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSNCMP_HPP
