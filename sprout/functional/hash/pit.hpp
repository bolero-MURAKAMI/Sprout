#ifndef SPROUT_FUNCTIONAL_HASH_PIT_HPP
#define SPROUT_FUNCTIONAL_HASH_PIT_HPP

#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sprout/pit.hpp>

namespace sprout {
	template<typename Container>
	SPROUT_CONSTEXPR std::size_t hash_value(sprout::pit<Container> const& v) {
		return sprout::to_hash(v.elem);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_PIT_HPP
