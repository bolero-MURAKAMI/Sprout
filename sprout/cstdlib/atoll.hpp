#ifndef SPROUT_CSTDLIB_ATOLL_HPP
#define SPROUT_CSTDLIB_ATOLL_HPP

#include <sprout/config.hpp>
#include <sprout/cstdlib/ascii_to_int.hpp>

namespace sprout {
	//
	// atoll
	//
	inline SPROUT_CONSTEXPR long long atoll(char const* str) {
		return sprout::ascii_to_int<long long>(str);
	}
	template<typename Char>
	inline SPROUT_CONSTEXPR long long atoll(Char const* str) {
		return sprout::ascii_to_int<long long>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_ATOLL_HPP
