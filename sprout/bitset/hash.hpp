#ifndef SPROUT_BITSET_HASH_HPP
#define SPROUT_BITSET_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/bitset/bitset.hpp>

namespace sprout {
	// 20.5.3 hash support

	template<std::size_t N>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::bitset<N> const& v) {
		return v.to_hash();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BITSET_HASH_HPP
