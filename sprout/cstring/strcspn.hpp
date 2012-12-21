#ifndef SPROUT_CSTRING_STRCSPN_HPP
#define SPROUT_CSTRING_STRCSPN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strchr.hpp>

namespace sprout {
	// 7.21.5.3  strcspn ä÷êî
	inline SPROUT_CONSTEXPR std::size_t
	strcspn(char const* s1, char const* s2) {
		return !*s1 || sprout::strchr(s2, *s1) ? 0
			: 1 + sprout::strcspn(s1 + 1, s2)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRCSPN_HPP
