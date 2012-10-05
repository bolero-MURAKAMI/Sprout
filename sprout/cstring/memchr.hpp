#ifndef SPROUT_CSTRING_MEMCHR_HPP
#define SPROUT_CSTRING_MEMCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		inline SPROUT_CONSTEXPR void const*
		memchr_impl(unsigned char const* s, unsigned char c, std::size_t n) {
			return !n ? 0
				: *s == c ? s
				: sprout::detail::memchr_impl(s + 1, c, n - 1)
			;
		}
	}	// namespace detail

	// 7.21.5.1  memchr ä÷êî
	inline SPROUT_CONSTEXPR void const*
	memchr(void const* s, int c, size_t n) {
		return sprout::detail::memchr_impl(static_cast<unsigned char const*>(s), static_cast<unsigned char>(c), n);
	}

	inline SPROUT_CONSTEXPR void*
	memchr(void* s, int c, size_t n) {
		return const_cast<void*>(
			sprout::detail::memchr_impl(static_cast<unsigned char*>(s), static_cast<unsigned char>(c), n)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_MEMCHR_HPP
