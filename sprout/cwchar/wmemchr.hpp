#ifndef SPROUT_CWCHAR_WMEMCHR_HPP
#define SPROUT_CWCHAR_WMEMCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/algorithm/find.hpp>

namespace sprout {
	namespace detail {
		inline SPROUT_CONSTEXPR wchar_t const*
		wmemchr_impl(wchar_t const* found, wchar_t const* last) {
			return found == last ? nullptr
				: found
				;
		}
		inline SPROUT_CONSTEXPR wchar_t*
		wmemchr_impl(wchar_t* found, wchar_t* last) {
			return found == last ? nullptr
				: found
				;
		}
	}	// namespace detail

	//
	// wmemchr
	//
	inline SPROUT_CONSTEXPR wchar_t const*
	wmemchr(wchar_t const* s, wchar_t c, size_t n) {
		return sprout::detail::wmemchr_impl(
			sprout::as_iterator_base(
				sprout::find(
					sprout::as_iterator(s), sprout::as_iterator(s, n),
					c
					)
				),
			s + n
			);
	}

	inline SPROUT_CONSTEXPR wchar_t*
	wmemchr(wchar_t* s, wchar_t c, size_t n) {
		return sprout::detail::wmemchr_impl(
			sprout::as_iterator_base(
				sprout::find(
					sprout::as_iterator(s), sprout::as_iterator(s, n),
					c
					)
				),
			s + n
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CWCHAR_WMEMCHR_HPP
