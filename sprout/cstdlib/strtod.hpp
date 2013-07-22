#ifndef SPROUT_CSTDLIB_STRTOD_HPP
#define SPROUT_CSTDLIB_STRTOD_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstdlib/str_to_float.hpp>

namespace sprout {
	//
	// strtod
	//
	template<typename Char>
	inline SPROUT_CONSTEXPR double
	strtod(Char const* str, Char** endptr) {
		return sprout::str_to_float<double>(str, endptr);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR double
	strtod(Char const* str, std::nullptr_t) {
		return sprout::str_to_float<double>(str);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR double
	strtod(Char const* str) {
		return sprout::str_to_float<double>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STRTOD_HPP
