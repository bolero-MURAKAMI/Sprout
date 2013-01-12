#ifndef SPROUT_CWCHAR_WCSNCMP_HPP
#define SPROUT_CWCHAR_WCSNCMP_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strncmp.hpp>

namespace sprout {
	//
	// wcsncmp
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR int
	wcsncmp(wchar_t const* s1, wchar_t const* s2, std::size_t n) {
		return sprout::strncmp(s1, s2, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSNCMP_HPP
