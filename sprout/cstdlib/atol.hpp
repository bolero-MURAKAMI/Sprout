#ifndef SPROUT_CSTDLIB_ATOL_HPP
#define SPROUT_CSTDLIB_ATOL_HPP

#include <sprout/config.hpp>
#include <sprout/cstdlib/decimal_to_int.hpp>

namespace sprout {
	//
	// atol
	//
	inline SPROUT_CONSTEXPR long atol(char const* str) {
		return sprout::decimal_to_int<long>(str);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR int atol(Char const* str) {
		return sprout::decimal_to_int<int>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_ATOL_HPP
