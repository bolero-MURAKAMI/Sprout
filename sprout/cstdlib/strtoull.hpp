#ifndef SPROUT_CSTDLIB_STRTTOULL_HPP
#define SPROUT_CSTDLIB_STRTTOULL_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstdlib/str_to_int.hpp>

namespace sprout {
	//
	// strtoul
	//
	inline SPROUT_CONSTEXPR unsigned long long
	strtoull(char const* str, char** endptr, int base = 10) {
		return sprout::str_to_int<unsigned long long>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR unsigned long long
	strtoull(Char const* str, Char** endptr, int base = 10) {
		return sprout::str_to_int<unsigned long long>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR unsigned long long
	strtoull(Char const* str, std::nullptr_t, int base = 10) {
		return sprout::str_to_int<unsigned long long>(str, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR unsigned long long
	strtoull(Char const* str, int base = 10) {
		return sprout::str_to_int<unsigned long long>(str, base);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STRTTOULL_HPP
