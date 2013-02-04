#ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUES_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_VALUES_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/functional/hash/hash_values_combine.hpp>

namespace sprout {
	//
	// hash_values
	//
	template<typename... Args>
	inline SPROUT_CONSTEXPR std::size_t
	hash_values(Args const&... args) {
		return sprout::hash_values_combine(0, args...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUES_HPP
