#ifndef SPROUT_CWCHAR_WCSCSPN_HPP
#define SPROUT_CWCHAR_WCSCSPN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strcspn.hpp>

namespace sprout {
	//
	// wcscspn
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR std::size_t
	wcscspn(wchar_t const* s1, wchar_t const* s2) {
		return sprout::strcspn(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSCSPN_HPP
