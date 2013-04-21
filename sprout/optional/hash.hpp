#ifndef SPROUT_OPTIONAL_HASH_HPP
#define SPROUT_OPTIONAL_HASH_HPP

#include <cstddef>
#include <functional>
#include <sprout/config.hpp>
#include <sprout/optional/optional.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::optional<T> const& v) {
		return v.is_initialized() ? sprout::to_hash(*v)
			: 0
			;
	}
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// hash
	//
	template<typename T>
	struct hash<sprout::optional<T> >
		: public sprout::hash<sprout::optional<T> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_OPTIONAL_HASH_HPP
