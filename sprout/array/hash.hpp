#ifndef SPROUT_ARRAY_HASH_HPP
#define SPROUT_ARRAY_HASH_HPP

#include <cstddef>
#include <functional>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::array<T, N> const& v) {
		return sprout::hash_range(v);
	}
}	// namespace sprout

namespace std {
	//
	// hash
	//
	template<typename T, std::size_t N>
	struct hash<sprout::array<T, N> >
		: public sprout::hash<sprout::array<T, N> >
	{};
}	// namespace std

#endif	// #ifndef SPROUT_ARRAY_HASH_HPP
