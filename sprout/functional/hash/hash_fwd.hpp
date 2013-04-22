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
	SPROUT_CONSTEXPR std::size_t to_hash(T&& v);

	//
	// hash_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(T const& v);

	//
	// hash_combine
	//
	template<typename... Args>
	inline SPROUT_CONSTEXPR std::size_t
	hash_combine(std::size_t seed, Args const&... args);

	//
	// hash_values
	//
	template<typename... Args>
	inline SPROUT_CONSTEXPR std::size_t
	hash_values(Args const&... args);

	//
	// hash_range
	//
	template<typename Iterator>
	SPROUT_CONSTEXPR std::size_t hash_range(std::size_t seed, Iterator first, Iterator last);
	template<typename Iterator>
	SPROUT_CONSTEXPR std::size_t hash_range(Iterator first, Iterator last);
	template<typename InputRange>
	SPROUT_CONSTEXPR std::size_t hash_range(std::size_t seed, InputRange const& rng);
	template<typename InputRange>
	SPROUT_CONSTEXPR std::size_t hash_range(InputRange const& rng);

	//
	// hash_value_traits
	//
	template<typename T>
	struct hash_value_traits;
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_FWD_HPP
