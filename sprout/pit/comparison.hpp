#ifndef SPROUT_PIT_COMPARISON_HPP
#define SPROUT_PIT_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/pit/pit.hpp>

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
	inline SPROUT_CONSTEXPR bool operator==(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return lhs.front() == rhs.front();
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool operator!=(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool operator<(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return lhs.front() < rhs.front();
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool operator>(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return rhs < lhs;
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool operator<=(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool operator>=(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_PIT_COMPARISON_HPP
