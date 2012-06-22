#ifndef SPROUT_ARRAY_COMPARISON_HPP
#define SPROUT_ARRAY_COMPARISON_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

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
	inline SPROUT_CONSTEXPR bool operator==(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool operator!=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool operator<(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool operator>(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool operator<=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool operator>=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_COMPARISON_HPP
