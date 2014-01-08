/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_UNIQUE_SEED_HPP
#define SPROUT_RANDOM_UNIQUE_SEED_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/functional/hash.hpp>
#include <sprout/preprocessor/unique_string.hpp>

namespace sprout {
	//
	// make_seed
	//
	template<typename T>
	SPROUT_CONSTEXPR std::uint_least32_t
	make_seed(T const& v) {
		return static_cast<std::uint_least32_t>(sprout::to_hash(v));
	}

	namespace detail {
		template<std::size_t N, typename T, typename... Args>
		SPROUT_CONSTEXPR typename std::enable_if<
			sizeof...(Args) + 1 == N,
			sprout::array<std::uint_least32_t, N>
		>::type
		make_seed_seq_impl(T const&, std::size_t seed, Args const&... args) {
			return sprout::array<std::uint_least32_t, N>{{args..., static_cast<std::uint_least32_t>(seed)}};
		}
		template<std::size_t N, typename T, typename... Args>
		SPROUT_CONSTEXPR typename std::enable_if<
			sizeof...(Args) + 1 != N,
			sprout::array<std::uint_least32_t, N>
		>::type
		make_seed_seq_impl(T const& v, std::size_t seed, Args const&... args) {
			return sprout::detail::make_seed_seq_impl<N>(v, sprout::hash_combine(seed, v), args..., static_cast<std::uint_least32_t>(seed));
		}
	}	// namespace detail
	//
	// make_seed_seq
	//
	template<std::size_t N, typename T>
	SPROUT_CONSTEXPR sprout::array<std::uint_least32_t, N>
	make_seed_seq(T const& v) {
		return sprout::detail::make_seed_seq_impl<N>(v, sprout::to_hash(v));
	}
}	// namespace sprout

//
// SPROUT_UNIQUE_SEED
//
#define SPROUT_UNIQUE_SEED (::sprout::make_seed(SPROUT_PP_UNIQUE_STRING))

//
// SPROUT_UNIQUE_SEED_SEQ
//
#define SPROUT_UNIQUE_SEED_SEQ(N) (::sprout::make_seed_seq<N>(SPROUT_PP_UNIQUE_STRING))

#endif	// #ifndef SPROUT_RANDOM_UNIQUE_SEED_HPP
