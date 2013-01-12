#ifndef SPROUT_CWCHAR_WCSCHR_HPP
#define SPROUT_CWCHAR_WCSCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strchr.hpp>

namespace sprout {
	//
	// wcschr
	//
	//	recursion depth:
	//		O(log N)
	//
	inline SPROUT_CONSTEXPR wchar_t const*
	wcschr(wchar_t const* s, wchar_t c) {
		return sprout::strchr(s, c);
	}
	inline SPROUT_CONSTEXPR wchar_t*
	wcschr(wchar_t* s, wchar_t c) {
		return sprout::strchr(s, c);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSCHR_HPP
