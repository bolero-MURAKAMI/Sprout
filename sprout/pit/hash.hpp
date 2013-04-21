#ifndef SPROUT_PIT_HASH_HPP
#define SPROUT_PIT_HASH_HPP

#include <cstddef>
#include <functional>
#include <sprout/config.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::pit<Container> const& v) {
		return sprout::to_hash(v.elem);
	}
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// hash
	//
	template<typename Container>
	struct hash<sprout::pit<Container> >
		: public sprout::hash<sprout::pit<Container> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_PIT_HASH_HPP
