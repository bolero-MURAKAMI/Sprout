#ifndef SPROUT_FUNCTIONAL_HASH_STD_ARRAY_HPP
#define SPROUT_FUNCTIONAL_HASH_STD_ARRAY_HPP

#include <cstddef>
#include <array>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_value_traits.hpp>
#include <sprout/functional/hash/hash_range.hpp>

namespace sprout {
	//
	// hash_value_traits
	//
	template<typename T, std::size_t N>
	struct hash_value_traits<std::array<T, N> > {
	public:
		static SPROUT_CONSTEXPR std::size_t
		hash_value(std::array<T, N> const& v) {
			return sprout::hash_range(v);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_STD_ARRAY_HPP
