#ifndef SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_ARRAY_HPP
#define SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_ARRAY_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash.hpp>
#include <sscrisk/cel/array.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sscrisk::cel::array<T, N> const& v) {
		return sprout::hash_range(v.begin(), v.end());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_ARRAY_HPP
