#ifndef SPROUT_CSTRING_STRLEN_HPP
#define SPROUT_CSTRING_STRLEN_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		inline SPROUT_CONSTEXPR std::size_t strlen_impl(char const* s, std::size_t n) {
			return !*s ? n :
				sprout::detail::strlen_impl(s + 1, n + 1)
				;
		}
	}	// namespace detail

	// 7.21.6.3  strlen ä÷êî
	inline SPROUT_CONSTEXPR std::size_t strlen(char const* s) {
		return sprout::detail::strlen_impl(s, 0);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRLEN_HPP
