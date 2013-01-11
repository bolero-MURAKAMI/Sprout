#ifndef SPROUT_CWCHAR_WCSLEN_HPP
#define SPROUT_CWCHAR_WCSLEN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/find.hpp>

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
		return sprout::distance(
			sprout::as_iterator(s),
			sprout::find(sprout::as_iterator(s), sprout::as_iterator(s, n), L'\0')
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSLEN_HPP
