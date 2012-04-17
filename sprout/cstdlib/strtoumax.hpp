#ifndef SPROUT_CSTDLIB_STRTTOUMAX_HPP
#define SPROUT_CSTDLIB_STRTTOUMAX_HPP

#include <cstddef>
#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/cstdlib/str_to_int.hpp>

namespace sprout {
	//
	// strtoul
	//
	inline SPROUT_CONSTEXPR std::uintmax_t strtoumax(char const* str, char** endptr, int base = 10){
		return sprout::str_to_int<std::uintmax_t>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR std::uintmax_t strtoumax(Char const* str, Char** endptr, int base = 10){
		return sprout::str_to_int<std::uintmax_t>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR std::uintmax_t strtoumax(Char const* str, std::nullptr_t endptr, int base = 10){
		return sprout::str_to_int<std::uintmax_t>(str, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR std::uintmax_t strtoumax(Char const* str, int base = 10){
		return sprout::str_to_int<std::uintmax_t>(str, base);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STRTTOUMAX_HPP
