#ifndef SPROUT_BITSET_BITWISE_HPP
#define SPROUT_BITSET_BITWISE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/bitset/bitset.hpp>

namespace sprout {
	// 20.5.4 bitset operators:

	template<std::size_t N>
	inline SPROUT_CONSTEXPR sprout::bitset<N>
	operator&(sprout::bitset<N> const& lhs, sprout::bitset<N> const& rhs) SPROUT_NOEXCEPT {
		return sprout::bitset<N>(lhs.do_and(rhs));
	}
	template<std::size_t N>
	inline SPROUT_CONSTEXPR sprout::bitset<N>
	operator|(sprout::bitset<N> const& lhs, sprout::bitset<N> const& rhs) SPROUT_NOEXCEPT {
		return sprout::bitset<N>(lhs.do_or(rhs));
	}
	template<std::size_t N>
	inline SPROUT_CONSTEXPR sprout::bitset<N>
	operator^(sprout::bitset<N> const& lhs, sprout::bitset<N> const& rhs) SPROUT_NOEXCEPT {
		return sprout::bitset<N>(lhs.do_xor(rhs));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BITSET_BITWISE_HPP
