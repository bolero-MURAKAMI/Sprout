#ifndef SPROUT_FUNCTIONAL_HASH_HASH_COMBINE_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_COMBINE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/functional/hash/to_hash.hpp>

namespace sprout {
	//
	// hash_combine
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_combine(std::size_t seed, T const& v) {
		return seed ^ (sprout::to_hash(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_COMBINE_HPP
