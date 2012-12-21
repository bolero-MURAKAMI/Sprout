#ifndef SPROUT_CWCHAR_WCSNCMP_HPP
#define SPROUT_CWCHAR_WCSNCMP_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>
#include <sprout/cwchar/wcslen.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// wcsncmp
	//
	inline SPROUT_CONSTEXPR int
	wcsncmp(wchar_t const* s1, wchar_t const* s2, std::size_t n) {
		return sprout::tristate_lexicographical_compare(
			sprout::as_iterator(s1), sprout::as_iterator(s1, sprout::wcslen(s1, n)),
			sprout::as_iterator(s2), sprout::as_iterator(s2, sprout::wcslen(s2, n))
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSNCMP_HPP
