/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_GENERATE_ARRAY_HPP
#define SPROUT_RANDOM_GENERATE_ARRAY_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace random {
		//
		// generate_array
		//
		template<std::size_t N, typename URNG>
		inline SPROUT_CXX14_CONSTEXPR sprout::array<typename URNG::result_type, N>
		generate_array(URNG& rng) {
			sprout::array<typename URNG::result_type, N> result{{}};
			for (std::size_t i = 0; i != N; ++i) {
				result[i] = rng();
			}
			return result;
		}

		namespace detail {
			template<std::size_t N, typename URNG, typename Random, typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				(sizeof...(Args) + 1 == N),
				sprout::pair<sprout::array<typename URNG::result_type, N>, URNG> const
			>::type generate_array_impl(Random const& rnd, Args const&... args) {
				typedef sprout::pair<sprout::array<typename URNG::result_type, N>, URNG> const pair_type;
				return pair_type{
					sprout::array<typename URNG::result_type, N>{{args..., rnd.result()}},
					rnd.engine()
					};
			}
			template<std::size_t N, typename URNG, typename Random, typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				(sizeof...(Args) + 1 < N),
				sprout::pair<sprout::array<typename URNG::result_type, N>, URNG> const
			>::type generate_array_impl(Random const& rnd, Args const&... args) {
				return sprout::random::detail::generate_array_impl<N, URNG>(rnd(), args..., rnd.result());
			}
		}	// namespace detail
		//
		// generate_array
		//
		template<std::size_t N, typename URNG>
		inline SPROUT_CONSTEXPR sprout::pair<sprout::array<typename URNG::result_type, N>, URNG> const
		generate_array(URNG const& rng) {
			return sprout::random::detail::generate_array_impl<N, URNG>(rng());
		}
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_GENERATE_ARRAY_HPP
