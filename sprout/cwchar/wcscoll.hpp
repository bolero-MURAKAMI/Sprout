#ifndef SPROUT_CWCHAR_WCSCOLL_HPP
#define SPROUT_CWCHAR_WCSCOLL_HPP

#include <sprout/config.hpp>
#include <sprout/cstring/strcoll.hpp>

namespace sprout {
	//
	// wcscoll
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR int
	wcscoll(wchar_t const* s1, wchar_t const* s2) {
		return sprout::strcoll(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSCOLL_HPP
