#ifndef SPROUT_FUNCTIONAL_HASH_TO_HASH_HPP
#define SPROUT_FUNCTIONAL_HASH_TO_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl hash_value(...);
}	// namespace sprout_adl

namespace sprout {
	//
	// to_hash
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	to_hash(T&& v) {
		using sprout::hash_value;
		using sprout_adl::hash_value;
		return hash_value(sprout::forward<T>(v));
	}
}	// namespace sprout

#include <sprout/functional/hash/hash_value.hpp>

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_TO_HASH_HPP
