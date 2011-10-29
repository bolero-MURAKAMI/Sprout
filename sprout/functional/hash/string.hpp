#ifndef SPROUT_FUNCTIONAL_HASH_STRING_HPP
#define SPROUT_FUNCTIONAL_HASH_STRING_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sprout/string.hpp>

namespace sprout {
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR std::size_t hash_value(sprout::basic_string<T, N, Traits> const& v) {
		return sprout::hash_range(v.begin(), v.end());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_STRING_HPP

