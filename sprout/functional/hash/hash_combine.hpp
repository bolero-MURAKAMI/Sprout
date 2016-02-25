/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_HASH_HASH_COMBINE_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_COMBINE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/functional/hash/to_hash.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_combine_impl(std::size_t seed) {
			return seed;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_combine_impl(std::size_t seed, T const& v) {
			return seed ^ (sprout::to_hash(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
		}
		template<typename Head, typename... Tail>
		inline SPROUT_CONSTEXPR std::size_t
		hash_combine_impl(std::size_t seed, Head const& head, Tail const&... tail) {
			return sprout::detail::hash_combine_impl(sprout::detail::hash_combine_impl(seed, head), tail...);
		}
	}	// namespace detail
	//
	// hash_combine
	//
	template<typename... Args>
	inline SPROUT_CONSTEXPR std::size_t
	hash_combine(std::size_t seed, Args const&... args) {
		return sprout::detail::hash_combine_impl(seed, args...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_COMBINE_HPP
