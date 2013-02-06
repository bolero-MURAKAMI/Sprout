#ifndef SPROUT_UTILITY_PAIR_HASH_HPP
#define SPROUT_UTILITY_PAIR_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T1, typename T2>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::pair<T1, T2> const& v) {
		return sprout::hash_values(v.first, v.second);
	}
}	// namespace sprout

namespace std {
	//
	// hash
	//
	template<typename T1, typename T2>
	struct hash<sprout::pair<T1, T2> >
		: public sprout::hash<sprout::pair<T1, T2> >
	{};
}	// namespace std

#endif	// #ifndef SPROUT_UTILITY_PAIR_HASH_HPP
