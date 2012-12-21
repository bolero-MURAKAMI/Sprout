#ifndef SPROUT_CWCHAR_WCSCSPN_HPP
#define SPROUT_CWCHAR_WCSCSPN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/cwchar/wcschr.hpp>

namespace sprout {
	//
	// wcscspn
	//
	inline SPROUT_CONSTEXPR std::size_t
	wcscspn(wchar_t const* s1, wchar_t const* s2) {
		return !*s1 || sprout::wcschr(s2, *s1) ? 0
			: 1 + sprout::wcscspn(s1 + 1, s2)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WCSCSPN_HPP
