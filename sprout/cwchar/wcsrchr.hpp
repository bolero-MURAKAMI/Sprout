#ifndef SPROUT_CWCHAR_WCSRCHR_HPP
#define SPROUT_CWCHAR_WCSRCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strrchr.hpp>

namespace sprout {
	//
	// wcsrchr
	//
	//	recursion depth:
	//		O(log N)
	//
	inline SPROUT_CONSTEXPR wchar_t const*
	wcsrchr(wchar_t const* s, wchar_t c) {
		return sprout::strrchr(s, c);
	}
	inline SPROUT_CONSTEXPR wchar_t*
	wcsrchr(wchar_t* s, wchar_t c) {
		return sprout::strrchr(s, c);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSRCHR_HPP
