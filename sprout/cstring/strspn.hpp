#ifndef SPROUT_CSTRING_STRSPN_HPP
#define SPROUT_CSTRING_XXX_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strchr.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		inline SPROUT_CONSTEXPR std::size_t strspn_impl(char const* s1, char const* s2, std::size_t n) {
			return !*s1 || !sprout::strchr(s2, *s1) ? n
				: sprout::detail::strspn_impl(s1 + 1, s2, n + 1)
				;
		}
	}	// namespace detail

	// 7.21.5.6  strspn ä÷êî
	inline SPROUT_CONSTEXPR std::size_t strspn(char const* s1, char const* s2) {
		return sprout::detail::strspn_impl(s1, s2, 0);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_XXX_HPP
