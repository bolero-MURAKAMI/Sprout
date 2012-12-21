#ifndef SPROUT_CSTRING_STRLEN_HPP
#define SPROUT_CSTRING_STRLEN_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	// 7.21.6.3  strlen ä÷êî
	inline SPROUT_CONSTEXPR std::size_t
	strlen(char const* s) {
		return !*s ? 0
			: 1 + sprout::strlen(s + 1)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRLEN_HPP
