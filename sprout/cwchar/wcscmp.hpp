#ifndef SPROUT_CWCHAR_WCSCMP_HPP
#define SPROUT_CWCHAR_WCSCMP_HPP

#include <sprout/config.hpp>
#include <sprout/cstring/strcmp.hpp>

namespace sprout {
	//
	// wcscmp
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR int
	wcscmp(wchar_t const* s1, wchar_t const* s2) {
		return sprout::strcmp(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSCMP_HPP
