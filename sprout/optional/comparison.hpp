#ifndef SPROUT_OPTIONAL_COMPARISON_HPP
#define SPROUT_OPTIONAL_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/optional/optional.hpp>
#include <sprout/utility/compare_pointees.hpp>

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
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_COMPARISON_HPP
