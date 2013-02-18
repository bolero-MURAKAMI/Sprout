#ifndef SPROUT_STRING_HASH_HPP
#define SPROUT_STRING_HASH_HPP

#include <cstddef>
#include <functional>
#include <sprout/config.hpp>
#include <sprout/string/string.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::basic_string<T, N, Traits> const& v) {
		return sprout::hash_range(v);
	}
}	// namespace sprout

namespace std {
	//
	// hash
	//
	template<typename T, std::size_t N, typename Traits>
	struct hash<sprout::basic_string<T, N, Traits> >
		: public sprout::hash<sprout::basic_string<T, N, Traits> >
	{};
}	// namespace std

#endif	// #ifndef SPROUT_STRING_HASH_HPP
