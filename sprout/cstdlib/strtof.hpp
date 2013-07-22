#ifndef SPROUT_CSTDLIB_STRTOF_HPP
#define SPROUT_CSTDLIB_STRTOF_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstdlib/str_to_float.hpp>

namespace sprout {
	//
	// strtof
	//
	template<typename Char>
	inline SPROUT_CONSTEXPR float
	strtof(Char const* str, Char** endptr) {
		return sprout::str_to_float<float>(str, endptr);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR float
	strtof(Char const* str, std::nullptr_t) {
		return sprout::str_to_float<float>(str);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR float
	strtof(Char const* str) {
		return sprout::str_to_float<float>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STRTOF_HPP
