#ifndef SPROUT_CSTDLIB_ATOI_HPP
#define SPROUT_CSTDLIB_ATOI_HPP

#include <sprout/config.hpp>
#include <sprout/cstdlib/decimal_to_int.hpp>

namespace sprout {
	//
	// atoi
	//
	inline SPROUT_CONSTEXPR int atoi(char const* str) {
		return sprout::decimal_to_int<int>(str);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR int atoi(Char const* str) {
		return sprout::decimal_to_int<int>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_ATOI_HPP
