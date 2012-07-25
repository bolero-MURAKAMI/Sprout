#ifndef SPROUT_ALGORITHM_FIXED_RANDOM_SWAP_RESULT_HPP
#define SPROUT_ALGORITHM_FIXED_RANDOM_SWAP_RESULT_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/random/uniform_int_distribution.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename UniformRandomNumberGenerator, typename Random>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				sprout::array<std::ptrdiff_t, 2>,
				typename std::decay<UniformRandomNumberGenerator>::type
			> make_random_swap_result_indexes_2(
				Random const& rnd,
				std::ptrdiff_t i0
				)
			{
				typedef sprout::tuples::tuple<
					sprout::array<std::ptrdiff_t, 2>,
					typename std::decay<UniformRandomNumberGenerator>::type
				> result_type;
				return result_type(
					sprout::array<std::ptrdiff_t, 2>{{i0, rnd.result()}},
					rnd.engine()
					);
			}
			template<typename UniformRandomNumberGenerator, typename Random>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				sprout::array<std::ptrdiff_t, 2>,
				typename std::decay<UniformRandomNumberGenerator>::type
			> make_random_swap_result_indexes_1(
				Random const& rnd
				)
			{
				return sprout::fixed::detail::make_random_swap_result_indexes_2<UniformRandomNumberGenerator>(
					rnd(),
					rnd.result()
					);
			}
			template<typename UniformRandomNumberGenerator>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				sprout::array<std::ptrdiff_t, 2>,
				typename std::decay<UniformRandomNumberGenerator>::type
			> make_random_swap_result_indexes(
				std::ptrdiff_t n,
				UniformRandomNumberGenerator&& g
				)
			{
				typedef sprout::tuples::tuple<
					sprout::array<std::ptrdiff_t, 2>,
					typename std::decay<UniformRandomNumberGenerator>::type
				> result_type;
				return n > 1
					? sprout::fixed::detail::make_random_swap_result_indexes_1<UniformRandomNumberGenerator>(
						sprout::random::uniform_int_distribution<std::ptrdiff_t>(0, n - 1)(sprout::forward<UniformRandomNumberGenerator>(g))
						)
					: result_type(
						sprout::array<std::ptrdiff_t, 2>{{}},
						sprout::forward<UniformRandomNumberGenerator>(g)
						)
					;
			}
			template<typename UniformRandomNumberGenerator, typename Container, typename RandomSwapped>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				typename sprout::fixed::result_of::algorithm<Container>::type,
				typename std::decay<UniformRandomNumberGenerator>::type
			> random_swap_result_impl_1(
				Container const& cont,
				RandomSwapped const& random_swapped
				)
			{
				typedef sprout::tuples::tuple<
					typename sprout::fixed::result_of::algorithm<Container>::type,
					typename std::decay<UniformRandomNumberGenerator>::type
				> result_type;
				return sprout::tuples::get<0>(random_swapped)[0] == sprout::tuples::get<0>(random_swapped)[1]
					? result_type(
						sprout::deep_copy(cont),
						sprout::tuples::get<1>(random_swapped)
						)
					: result_type(
						sprout::fixed::swap_element(
							cont,
							sprout::next(sprout::begin(cont), sprout::tuples::get<0>(random_swapped)[0]),
							sprout::next(sprout::begin(cont), sprout::tuples::get<0>(random_swapped)[1])
							),
						sprout::tuples::get<1>(random_swapped)
						)
					;
			}
			template<typename Container, typename UniformRandomNumberGenerator>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				typename sprout::fixed::result_of::algorithm<Container>::type,
				typename std::decay<UniformRandomNumberGenerator>::type
			> random_swap_result_impl(
				Container const& cont,
				UniformRandomNumberGenerator&& g,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::fixed::detail::random_swap_result_impl_1<UniformRandomNumberGenerator>(
					cont,
					sprout::fixed::detail::make_random_swap_result_indexes(
						size,
						sprout::forward<UniformRandomNumberGenerator>(g)
						)
					);
			}
		}	// namespace detail
		//
		// random_swap_result
		//
		template<typename Container, typename UniformRandomNumberGenerator>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<
			typename sprout::fixed::result_of::algorithm<Container>::type,
			typename std::decay<UniformRandomNumberGenerator>::type
		> random_swap_result(
			Container const& cont,
			UniformRandomNumberGenerator&& g
			)
		{
			return sprout::fixed::detail::random_swap_result_impl(
				cont,
				sprout::forward<UniformRandomNumberGenerator>(g),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::random_swap_result;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_RANDOM_SWAP_RESULT_HPP
