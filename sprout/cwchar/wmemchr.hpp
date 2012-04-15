#ifndef SPROUT_CWCHAR_WMEMCHR_HPP
#define SPROUT_CWCHAR_WMEMCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		inline SPROUT_CONSTEXPR wchar_t const* wmemchr_impl(wchar_t const* s, wchar_t c, std::size_t n) {
			return !n ? 0
				: *s == c ? s
				: sprout::detail::wmemchr_impl(s + 1, c, n - 1)
			;
		}
	}	// namespace detail

	inline SPROUT_CONSTEXPR wchar_t const* wmemchr(wchar_t const* s, wchar_t c, size_t n) {
		return sprout::detail::wmemchr_impl(s, c, n);
	}

	inline SPROUT_CONSTEXPR wchar_t* wmemchr(wchar_t* s, wchar_t c, size_t n) {
		return const_cast<wchar_t*>(
			sprout::detail::wmemchr_impl(s, c, n)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WMEMCHR_HPP
