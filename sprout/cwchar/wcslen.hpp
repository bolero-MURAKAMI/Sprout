#ifndef SPROUT_CWCHAR_WCSLEN_HPP
#define SPROUT_CWCHAR_WCSLEN_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	inline SPROUT_CONSTEXPR std::size_t
	wcslen(wchar_t const* s) {
		return !*s ? 0
			: 1 + sprout::wcslen(s + 1)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSLEN_HPP
