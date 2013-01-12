#ifndef SPROUT_CWCHAR_WCSLEN_HPP
#define SPROUT_CWCHAR_WCSLEN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strlen.hpp>

namespace sprout {
	//
	// wcslen
	//
	//	recursion depth:
	//		O(log N)
	//
	inline SPROUT_CONSTEXPR std::size_t
	wcslen(wchar_t const* s) {
		return sprout::strlen(s);
	}
	inline SPROUT_CONSTEXPR std::size_t
	wcslen(wchar_t const* s, std::size_t n) {
		return sprout::strlen(s, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSLEN_HPP
