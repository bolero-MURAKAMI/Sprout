#ifndef SPROUT_CWCHAR_WMEMCMP_HPP
#define SPROUT_CWCHAR_WMEMCMP_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		inline SPROUT_CONSTEXPR int
		wmemcmp_impl(wchar_t const* s1, wchar_t const* s2, std::size_t n) {
			return !n ? 0
				: *s1 == *s2 ? sprout::detail::wmemcmp_impl(s1 + 1, s2 + 1, n - 1)
				: *s1 - *s2
				;
		}
	}	// namespace detail

	inline SPROUT_CONSTEXPR int
	wmemcmp(wchar_t const* s1, wchar_t const* s2, std::size_t n) {
		return sprout::detail::wmemcmp_impl(s1, s2, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WMEMCMP_HPP
