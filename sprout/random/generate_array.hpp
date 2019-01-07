/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_GENERATE_ARRAY_HPP
#define SPROUT_RANDOM_GENERATE_ARRAY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array/array.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/random/results.hpp>
#include <sprout/generator/results.hpp>

namespace sprout {
	namespace random {
		//
		// generate_array
		//
		template<std::size_t N, typename RandomNumberGenerator>
		inline SPROUT_CXX14_CONSTEXPR sprout::array<typename RandomNumberGenerator::result_type, N>
		generate_array(RandomNumberGenerator& rng) {
			sprout::array<typename RandomNumberGenerator::result_type, N> result{{}};
			for (std::size_t i = 0; i != N; ++i) {
				result[i] = rng();
			}
			return result;
		}
		template<std::size_t N, typename RandomNumberGenerator, typename Distribution>
		inline SPROUT_CXX14_CONSTEXPR sprout::array<typename std::remove_reference<Distribution>::type::result_type, N>
		generate_array(RandomNumberGenerator& rng, Distribution&& dist) {
			sprout::array<typename std::remove_reference<Distribution>::type::result_type, N> result{{}};
			for (std::size_t i = 0; i != N; ++i) {
				result[i] = SPROUT_FORWARD(Distribution, dist)(rng);
			}
			return result;
		}

		namespace detail {
			template<std::size_t N, typename RandomNumberGenerator, typename Random, typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				(sizeof...(Args) + 1 == N),
				sprout::pair<
					sprout::array<typename sprout::generators::results::generated_value<RandomNumberGenerator const>::type, N>,
					typename sprout::generators::results::next_generator<RandomNumberGenerator const>::type
				> const
			>::type generate_array_impl(Random const& rnd, Args const&... args) {
				typedef sprout::pair<
					sprout::array<typename sprout::generators::results::generated_value<RandomNumberGenerator const>::type, N>,
					typename sprout::generators::results::next_generator<RandomNumberGenerator const>::type
				> const pair_type;
				return pair_type{
					sprout::array<typename RandomNumberGenerator::result_type, N>{{args..., sprout::random::result(rnd)}},
					sprout::random::next(rnd)
					};
			}
			template<std::size_t N, typename RandomNumberGenerator, typename Random, typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				(sizeof...(Args) + 1 < N),
				sprout::pair<
					sprout::array<typename sprout::generators::results::generated_value<RandomNumberGenerator const>::type, N>,
					typename sprout::generators::results::next_generator<RandomNumberGenerator const>::type
				> const
			>::type generate_array_impl(Random const& rnd, Args const&... args) {
				return sprout::random::detail::generate_array_impl<N, RandomNumberGenerator>(
					sprout::random::next(rnd)(),
					args..., sprout::random::result(rnd)
					);
			}
		}	// namespace detail
		//
		// generate_array
		//
		template<std::size_t N, typename RandomNumberGenerator>
		inline SPROUT_CONSTEXPR sprout::pair<
			sprout::array<typename sprout::generators::results::generated_value<RandomNumberGenerator const>::type, N>,
			typename sprout::generators::results::next_generator<RandomNumberGenerator const>::type
		> const
		generate_array(RandomNumberGenerator const& rng) {
			return sprout::random::detail::generate_array_impl<N, RandomNumberGenerator>(rng());
		}
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_GENERATE_ARRAY_HPP
