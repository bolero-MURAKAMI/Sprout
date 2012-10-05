#ifndef SPROUT_CSTRING_STRCSPN_HPP
#define SPROUT_CSTRING_STRCSPN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strchr.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		inline SPROUT_CONSTEXPR std::size_t
		strcspn_impl(char const* s1, char const* s2, std::size_t n) {
			return !*s1 || sprout::strchr(s2, *s1) ? n
				: sprout::detail::strcspn_impl(s1 + 1, s2, n + 1)
				;
		}
	}	// amespace detail

	// 7.21.5.3  strcspn ä÷êî
	inline SPROUT_CONSTEXPR std::size_t
	strcspn(char const* s1, char const* s2) {
		return sprout::detail::strcspn_impl(s1, s2, 0);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRCSPN_HPP
