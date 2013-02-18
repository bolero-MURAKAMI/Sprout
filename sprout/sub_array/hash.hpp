#ifndef SPROUT_SUB_ARRAY_HASH_HPP
#define SPROUT_SUB_ARRAY_HASH_HPP

#include <cstddef>
#include <functional>
#include <sprout/config.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename Container>
	SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::sub_array<Container> const& v) {
		return sprout::hash_range(v);
	}
}	// namespace sprout

namespace std {
	//
	// hash
	//
	template<typename Container>
	struct hash<sprout::sub_array<Container> >
		: public sprout::hash<sprout::sub_array<Container> >
	{};
}	// namespace std

#endif	// #ifndef SPROUT_SUB_ARRAY_HASH_HPP
