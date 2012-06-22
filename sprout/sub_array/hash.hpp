#ifndef SPROUT_SUB_ARRAY_HASH_HPP
#define SPROUT_SUB_ARRAY_HASH_HPP

#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sprout/sub_array/sub_array.hpp>

namespace sprout {
	template<typename Container>
	SPROUT_CONSTEXPR std::size_t hash_value(sprout::sub_array<Container> const& v) {
		return sprout::hash_range(v.begin(), v.end());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_SUB_ARRAY_HASH_HPP
