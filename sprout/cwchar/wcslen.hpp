#ifndef SPROUT_CWCHAR_WCSLEN_HPP
#define SPROUT_CWCHAR_WCSLEN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// wcslen
	//
	inline SPROUT_CONSTEXPR std::size_t
	wcslen(wchar_t const* s) {
		return !*s ? 0
			: 1 + sprout::wcslen(s + 1)
			;
	}

	inline SPROUT_CONSTEXPR std::size_t
	wcslen(wchar_t const* s, std::size_t n) {
		return NS_SSCRISK_CEL_OR_SPROUT::distance(
			sprout::as_iterator(s),
			NS_SSCRISK_CEL_OR_SPROUT::find(sprout::as_iterator(s), sprout::as_iterator(s, n), L'\0')
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSLEN_HPP
