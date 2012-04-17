#ifndef SPROUT_CSTDLIB_STRTOIMAX_HPP
#define SPROUT_CSTDLIB_STRTOIMAX_HPP

#include <cstddef>
#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/cstdlib/str_to_int.hpp>

namespace sprout {
	//
	// strtoimax
	//
	inline SPROUT_CONSTEXPR std::intmax_t strtoimax(char const* str, char** endptr, int base = 10){
		return sprout::str_to_int<std::intmax_t>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR std::intmax_t strtoimax(Char const* str, Char** endptr, int base = 10){
		return sprout::str_to_int<std::intmax_t>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR std::intmax_t strtoimax(Char const* str, std::nullptr_t endptr, int base = 10){
		return sprout::str_to_int<std::intmax_t>(str, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR std::intmax_t strtoimax(Char const* str, int base = 10){
		return sprout::str_to_int<std::intmax_t>(str, base);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STRTOIMAX_HPP
