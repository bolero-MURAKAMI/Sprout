#ifndef SPROUT_CSTDLIB_STRTOLD_HPP
#define SPROUT_CSTDLIB_STRTOLD_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstdlib/str_to_float.hpp>

namespace sprout {
	//
	// strtold
	//
	template<typename Char>
	inline SPROUT_CONSTEXPR long double strtold(Char const* str, Char** endptr){
		return sprout::str_to_float<long double>(str, endptr);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR long double strtold(Char const* str, std::nullptr_t endptr){
		return sprout::str_to_float<long double>(str);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR long double strtold(Char const* str){
		return sprout::str_to_float<long double>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STRTOLD_HPP
