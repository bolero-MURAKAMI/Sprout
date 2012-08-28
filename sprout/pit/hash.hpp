#ifndef SPROUT_PIT_HASH_HPP
#define SPROUT_PIT_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	template<typename Container>
	inline SPROUT_CONSTEXPR std::size_t hash_value(sprout::pit<Container> const& v) {
		return sprout::hash_range(v.begin(), v.end());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_PIT_HASH_HPP
