#ifndef SPROUT_ARRAY_COMPARISON_HPP
#define SPROUT_ARRAY_COMPARISON_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/algorithm/equal.hpp>
#include <sprout/algorithm/lexicographical_compare.hpp>

namespace sprout {
	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return sprout::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return sprout::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_COMPARISON_HPP
