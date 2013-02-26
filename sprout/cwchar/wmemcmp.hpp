#ifndef SPROUT_CWCHAR_WMEMCMP_HPP
#define SPROUT_CWCHAR_WMEMCMP_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>

namespace sprout {
	//
	// wmemcmp
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR int
	wmemcmp(wchar_t const* s1, wchar_t const* s2, std::size_t n) {
		return sprout::tristate_lexicographical_compare(
			sprout::ptr_index(s1), sprout::ptr_index(s1, n),
			sprout::ptr_index(s2), sprout::ptr_index(s2, n)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WMEMCMP_HPP
