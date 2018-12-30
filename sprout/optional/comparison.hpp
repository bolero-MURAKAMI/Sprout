/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPTIONAL_COMPARISON_HPP
#define SPROUT_OPTIONAL_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/utility/compare_pointees.hpp>
#include <sprout/optional/optional.hpp>
#include <sprout/optional/nullopt.hpp>

namespace sprout {
	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::optional<T> const& lhs, sprout::optional<T> const& rhs) {
		return sprout::equal_pointees(lhs, rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::optional<T> const& lhs, sprout::optional<T> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::optional<T> const& lhs, sprout::optional<T> const& rhs) {
		return sprout::less_pointees(lhs, rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::optional<T> const& lhs, sprout::optional<T> const& rhs) {
		return rhs < lhs;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::optional<T> const& lhs, sprout::optional<T> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::optional<T> const& lhs, sprout::optional<T> const& rhs) {
		return !(lhs < rhs);
	}

	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::optional<T> const& lhs, sprout::nullopt_t) SPROUT_NOEXCEPT {
		return !lhs;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::nullopt_t, sprout::optional<T> const& rhs) SPROUT_NOEXCEPT {
		return !rhs;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::optional<T> const& lhs, sprout::nullopt_t) SPROUT_NOEXCEPT {
		return bool(lhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::nullopt_t, sprout::optional<T> const& rhs) SPROUT_NOEXCEPT {
		return bool(rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::optional<T> const&, sprout::nullopt_t) SPROUT_NOEXCEPT {
		return false;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::nullopt_t, sprout::optional<T> const& rhs) SPROUT_NOEXCEPT {
		return bool(rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::optional<T> const& lhs, sprout::nullopt_t) SPROUT_NOEXCEPT {
		return bool(lhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::nullopt_t, sprout::optional<T> const&) SPROUT_NOEXCEPT {
		return false;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::optional<T> const& lhs, sprout::nullopt_t) SPROUT_NOEXCEPT {
		return !lhs;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::nullopt_t, sprout::optional<T> const&) SPROUT_NOEXCEPT {
		return true;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::optional<T> const&, sprout::nullopt_t) SPROUT_NOEXCEPT {
		return true;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::nullopt_t, sprout::optional<T> const& rhs) SPROUT_NOEXCEPT {
		return !rhs;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_COMPARISON_HPP
