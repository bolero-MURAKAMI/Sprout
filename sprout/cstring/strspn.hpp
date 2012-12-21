#ifndef SPROUT_CSTRING_STRSPN_HPP
#define SPROUT_CSTRING_STRSPN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strchr.hpp>

namespace sprout {
	// 7.21.5.6  strspn ä÷êî
	inline SPROUT_CONSTEXPR std::size_t
	strspn(char const* s1, char const* s2) {
		return !*s1 || !sprout::strchr(s2, *s1) ? 0
			: 1 + sprout::strspn(s1 + 1, s2)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRSPN_HPP
