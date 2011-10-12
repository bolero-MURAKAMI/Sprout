#ifndef SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_UTILITY_HPP
#define SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_UTILITY_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sscrisk/cel/utility.hpp>

namespace sprout {
	template<typename T1, typename T2>
	SPROUT_CONSTEXPR std::size_t hash_value(sscrisk::cel::pair<T1, T2> const& v) {
		return sprout::hash_combine(sprout::hash_combine(0, v.first), v.second);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_UTILITY_HPP
