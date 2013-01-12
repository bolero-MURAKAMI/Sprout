#ifndef SPROUT_CWCHAR_WCSSPN_HPP
#define SPROUT_CWCHAR_WCSSPN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cstring/strspn.hpp>

namespace sprout {
	//
	// wcsspn
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR std::size_t
	wcsspn(wchar_t const* s1, wchar_t const* s2) {
		return sprout::strspn(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSSPN_HPP
