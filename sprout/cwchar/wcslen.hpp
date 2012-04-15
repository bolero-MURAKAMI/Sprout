#ifndef SPROUT_CWCHAR_WCSLEN_HPP
#define SPROUT_CWCHAR_WCSLEN_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		inline SPROUT_CONSTEXPR std::size_t wcslen_impl(wchar_t const* s, std::size_t n) {
			return !*s ? n :
				sprout::detail::wcslen_impl(s + 1, n + 1)
				;
		}
	}	// namespace detail

	inline SPROUT_CONSTEXPR std::size_t wcslen(wchar_t const* s) {
		return sprout::detail::wcslen_impl(s, 0);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSLEN_HPP
