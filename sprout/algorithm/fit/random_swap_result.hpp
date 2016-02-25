/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_RANDOM_SWAP_RESULT_HPP
#define SPROUT_ALGORITHM_FIT_RANDOM_SWAP_RESULT_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/fixed/random_swap_result.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename UniformRandomNumberGenerator, typename Shuffled>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				typename sprout::fit::results::algorithm<Container>::type,
				typename std::decay<UniformRandomNumberGenerator>::type
			>
			random_swap_result_impl_1(
				Shuffled const& random_swapd,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				typedef sprout::tuples::tuple<
					typename sprout::fit::results::algorithm<Container>::type,
					typename std::decay<UniformRandomNumberGenerator>::type
				> result_type;
				return result_type(
					sprout::sub_copy(
						sprout::get_internal(sprout::tuples::get<0>(random_swapd)),
						offset,
						offset + sprout::size(sprout::tuples::get<0>(random_swapd))
						),
					sprout::tuples::get<1>(random_swapd)
					);
			}
			template<typename Container, typename UniformRandomNumberGenerator>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				typename sprout::fit::results::algorithm<Container>::type,
				typename std::decay<UniformRandomNumberGenerator>::type
			>
			random_swap_result_impl(
				Container const& cont, UniformRandomNumberGenerator&& g,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::fit::detail::random_swap_result_impl_1<Container, UniformRandomNumberGenerator>(
					sprout::fixed::random_swap_result(cont, SPROUT_FORWARD(UniformRandomNumberGenerator, g)),
					offset
					);
			}
		}	// namespace detail
		//
		// random_swap_result
		//
		template<typename Container, typename UniformRandomNumberGenerator>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<
			typename sprout::fit::results::algorithm<Container>::type,
			typename std::decay<UniformRandomNumberGenerator>::type
		>
		random_swap_result(Container const& cont, UniformRandomNumberGenerator&& g) {
			return sprout::fit::detail::random_swap_result_impl(
				cont, SPROUT_FORWARD(UniformRandomNumberGenerator, g),
				sprout::internal_begin_offset(cont)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_RANDOM_SWAP_RESULT_HPP
