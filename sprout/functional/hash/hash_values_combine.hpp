#ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUES_COMBINE_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_VALUES_COMBINE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/functional/hash/hash_combine.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_values_combine_impl(std::size_t seed, T const& v) {
			return sprout::hash_combine(seed, v);
		}
		template<typename Head, typename... Tail>
		inline SPROUT_CONSTEXPR std::size_t
		hash_values_combine_impl(std::size_t seed, Head const& head, Tail const&... tail) {
			return sprout::detail::hash_values_combine_impl(sprout::hash_combine(seed, head), tail...);
		}
	}	// namespace detail

	//
	// hash_values_combine
	//
	template<typename... Args>
	inline SPROUT_CONSTEXPR std::size_t
	hash_values_combine(std::size_t seed, Args const&... args) {
		return sprout::detail::hash_values_combine_impl(seed, args...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUES_COMBINE_HPP
