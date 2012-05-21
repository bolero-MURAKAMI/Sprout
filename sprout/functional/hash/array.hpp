#ifndef SPROUT_FUNCTIONAL_HASH_ARRAY_HPP
#define SPROUT_FUNCTIONAL_HASH_ARRAY_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sprout/array.hpp>

namespace sprout {
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR std::size_t hash_value(sprout::array<T, N> const& v) {
		return sprout::hash_range(v.begin(), v.end());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_ARRAY_HPP
