#ifndef SPROUT_UUID_HASH_HPP
#define SPROUT_UUID_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/uuid/uuid.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::uuids::uuid const& v) {
		return sprout::hash_range(v);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_HASH_HPP
