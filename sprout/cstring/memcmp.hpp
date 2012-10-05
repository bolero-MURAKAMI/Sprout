#ifndef SPROUT_CSTRING_MEMCMP_HPP
#define SPROUT_CSTRING_MEMCMP_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		inline SPROUT_CONSTEXPR int
		memcmp_impl(unsigned char const* s1, unsigned char const* s2, std::size_t n) {
			return !n ? 0
				: *s1 == *s2 ? sprout::detail::memcmp_impl(s1 + 1, s2 + 1, n - 1)
				: *s1 - *s2
				;
		}
	}	// namespace detail

	// 7.21.4.1  memcmp ä÷êî
	inline SPROUT_CONSTEXPR int
	memcmp(void const* s1, void const* s2, std::size_t n) {
		return sprout::detail::memcmp_impl(
			static_cast<unsigned char const*>(s1),
			static_cast<unsigned char const*>(s2),
			n
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_MEMCMP_HPP
