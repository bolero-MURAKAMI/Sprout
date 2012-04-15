#ifndef SPROUT_CWCHAR_WCSCSPN_HPP
#define SPROUT_CWCHAR_WCSCSPN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strchr.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		inline SPROUT_CONSTEXPR std::size_t wcscspn_impl(wchar_t const* s1, wchar_t const* s2, std::size_t n) {
			return !*s1 || sprout::wcschr(s2, *s1) ? n
				: sprout::detail::wcscspn_impl(s1 + 1, s2, n + 1)
				;
		}
	}	// amespace detail

	inline SPROUT_CONSTEXPR std::size_t wcscspn(wchar_t const* s1, wchar_t const* s2) {
		return sprout::detail::wcscspn_impl(s1, s2, 0);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSCSPN_HPP
