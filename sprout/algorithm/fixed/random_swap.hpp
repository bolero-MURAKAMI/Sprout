#ifndef SPROUT_ALGORITHM_FIXED_RANDOM_SWAP_HPP
#define SPROUT_ALGORITHM_FIXED_RANDOM_SWAP_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/workaround/detail/uniform_int_distribution.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Random>
			inline SPROUT_CONSTEXPR sprout::array<std::ptrdiff_t, 2>
			make_random_swap_indexes_2(Random const& rnd, std::ptrdiff_t i0) {
				return sprout::array<std::ptrdiff_t, 2>{{i0, rnd.result()}};
			}
			template<typename Random>
			inline SPROUT_CONSTEXPR sprout::array<std::ptrdiff_t, 2>
			make_random_swap_indexes_1(Random const& rnd) {
				return sprout::fixed::detail::make_random_swap_indexes_2(
					rnd(),
					rnd.result()
					);
			}
			template<typename UniformRandomNumberGenerator>
			inline SPROUT_CONSTEXPR sprout::array<std::ptrdiff_t, 2>
			make_random_swap_indexes(std::ptrdiff_t n, UniformRandomNumberGenerator&& g) {
				return n > 1
					? sprout::fixed::detail::make_random_swap_indexes_1(
						SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION<std::ptrdiff_t>(0, n - 1)(
							sprout::forward<UniformRandomNumberGenerator>(g)
							)
						)
					: sprout::array<std::ptrdiff_t, 2>{{}}
					;
			}
			template<typename Container, typename RandomSwapped>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			random_swap_impl_1(Container const& cont, RandomSwapped const& random_swapped) {
				return random_swapped[0] == random_swapped[1]
					? sprout::deep_copy(cont)
					: sprout::fixed::swap_element(
						cont,
						sprout::next(sprout::begin(cont), random_swapped[0]),
						sprout::next(sprout::begin(cont), random_swapped[1])
						)
					;
			}
			template<typename Container, typename UniformRandomNumberGenerator>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			random_swap_impl(
				Container const& cont, UniformRandomNumberGenerator&& g,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::fixed::detail::random_swap_impl_1(
					cont,
					sprout::fixed::detail::make_random_swap_indexes(
						size,
						sprout::forward<UniformRandomNumberGenerator>(g)
						)
					);
			}
		}	// namespace detail
		//
		// random_swap
		//
		template<typename Container, typename UniformRandomNumberGenerator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		random_swap(Container const& cont, UniformRandomNumberGenerator&& g) {
			return sprout::fixed::detail::random_swap_impl(
				cont, sprout::forward<UniformRandomNumberGenerator>(g),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::random_swap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_RANDOM_SWAP_HPP
