#ifndef SPROUT_ARRAY_HASH_HPP
#define SPROUT_ARRAY_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sprout/array/array.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::array<T, N> const& v) {
		return sprout::hash_range(v.begin(), v.end());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_HASH_HPP
