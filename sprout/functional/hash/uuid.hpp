#ifndef SPROUT_FUNCTIONAL_HASH_UUID_HPP
#define SPROUT_FUNCTIONAL_HASH_UUID_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sprout/uuid/uuid.hpp>

namespace sprout {
	SPROUT_CONSTEXPR std::size_t hash_value(sprout::uuids::uuid const& v) {
		return sprout::hash_range(v.begin(), v.end());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_UUID_HPP
