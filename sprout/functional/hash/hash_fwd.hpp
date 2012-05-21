#ifndef SPROUT_FUNCTIONAL_HASH_HASH_FWD_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_FWD_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	//
	// hash
	//
	template<typename T>
	struct hash;

	//
	// to_hash
	//
	template<typename T>
	SPROUT_CONSTEXPR std::size_t to_hash(T const& v);

	//
	// hash_combine
	//
	template<typename T>
	SPROUT_CONSTEXPR std::size_t hash_combine(std::size_t seed, T const& v);

	//
	// hash_range
	//
	template<typename Iterator>
	SPROUT_CONSTEXPR std::size_t hash_range(Iterator first, Iterator last);
	template<typename Iterator>
	SPROUT_CONSTEXPR std::size_t hash_range(std::size_t seed, Iterator first, Iterator last);
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_FWD_HPP
