#ifndef SPROUT_SUB_ARRAY_COMPARISON_HPP
#define SPROUT_SUB_ARRAY_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/sub_array/sub_array.hpp>
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
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT::equal(sprout::begin(lhs), sprout::end(lhs), sprout::begin(rhs));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT::lexicographical_compare(
			sprout::begin(lhs), sprout::end(lhs),
			sprout::begin(rhs), sprout::end(rhs)
			);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return rhs < lhs;
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_SUB_ARRAY_COMPARISON_HPP
