#ifndef SPROUT_CSTDLIB_STRTOLL_HPP
#define SPROUT_CSTDLIB_STRTOLL_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstdlib/str_to_int.hpp>

namespace sprout {
	//
	// strtol
	//
	inline SPROUT_CONSTEXPR long long
	strtoll(char const* str, char** endptr, int base = 10) {
		return sprout::str_to_int<long long>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR long long
	strtoll(Char const* str, Char** endptr, int base = 10) {
		return sprout::str_to_int<long long>(str, endptr, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR long long
	strtoll(Char const* str, std::nullptr_t endptr, int base = 10) {
		return sprout::str_to_int<long long>(str, base);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR long long
	strtoll(Char const* str, int base = 10) {
		return sprout::str_to_int<long long>(str, base);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STRTOLL_HPP
