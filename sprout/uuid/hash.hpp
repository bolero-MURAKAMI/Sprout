#ifndef SPROUT_UUID_HASH_HPP
#define SPROUT_UUID_HASH_HPP

#include <cstddef>
#include <functional>
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

namespace std {
	//
	// hash
	//
	template<>
	struct hash<sprout::uuids::uuid>
		: public sprout::hash<sprout::uuids::uuid>
	{};
}	// namespace std

#endif	// #ifndef SPROUT_UUID_HASH_HPP
