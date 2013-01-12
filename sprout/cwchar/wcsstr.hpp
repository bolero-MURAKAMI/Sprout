#ifndef SPROUT_CWCHAR_WCSSTR_HPP
#define SPROUT_CWCHAR_WCSSTR_HPP

#include <sprout/config.hpp>
#include <sprout/cstring/strstr.hpp>

namespace sprout {
	//
	// wcsstr
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR wchar_t const*
	wcsstr(wchar_t const* s1, wchar_t const* s2) {
		return sprout::strstr(s1, s2);
	}
	inline SPROUT_CONSTEXPR wchar_t*
	wcsstr(wchar_t* s1, wchar_t const* s2) {
		return sprout::strstr(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSSTR_HPP
