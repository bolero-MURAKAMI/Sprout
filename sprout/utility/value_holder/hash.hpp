#ifndef SPROUT_UTILITY_VALUE_HOLDER_HASH_HPP
#define SPROUT_UTILITY_VALUE_HOLDER_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// hash_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::value_holder<T> const& v) {
		return sprout::to_hash(*v)
			;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::value_holder<T&> const& v) {
		return v.is_initialized() ? sprout::to_hash(*v)
			: 0
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_VALUE_HOLDER_HASH_HPP
