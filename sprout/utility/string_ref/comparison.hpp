/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_REF_COMPARISON_HPP
#define SPROUT_UTILITY_STRING_REF_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/string/string.hpp>

namespace sprout {
	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::basic_string_ref<T, Traits> const& lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return lhs.compare(rhs) == 0;
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::basic_string_ref<T, Traits> const& lhs, T const* rhs) {
		return lhs.compare(rhs) == 0;
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator==(T const* lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return 0 == rhs.compare(lhs);
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::basic_string_ref<T, Traits> const& lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::basic_string_ref<T, Traits> const& lhs, T const* rhs) {
		return !(lhs == rhs);
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator!=(T const* lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::basic_string_ref<T, Traits> const& lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return lhs.compare(rhs) < 0;
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::basic_string_ref<T, Traits> const& lhs, T const* rhs) {
		return lhs.compare(rhs) < 0;
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator<(T const* lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return 0 < rhs.compare(lhs);
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::basic_string_ref<T, Traits> const& lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::basic_string_ref<T, Traits> const& lhs, T const* rhs) {
		return rhs < lhs;
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator>(T const* lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::basic_string_ref<T, Traits> const& lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::basic_string_ref<T, Traits> const& lhs, T const* rhs) {
		return !(rhs < lhs);
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator<=(T const* lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::basic_string_ref<T, Traits> const& lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::basic_string_ref<T, Traits> const& lhs, T const* rhs) {
		return !(lhs < rhs);
	}
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR bool
	operator>=(T const* lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_STRING_REF_COMPARISON_HPP
