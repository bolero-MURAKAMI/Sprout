/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_SHUFFLE_HPP
#define SPROUT_ALGORITHM_FIXED_SHUFFLE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/array/array.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/numeric/fixed/iota.hpp>
#include <sprout/random/results.hpp>
#include <sprout/workaround/detail/uniform_int_distribution.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<std::size_t N, typename Random>
			inline SPROUT_CONSTEXPR sprout::array<std::ptrdiff_t, N>
			make_shuffle_indexes_1(std::ptrdiff_t n, Random const& rnd, sprout::array<std::ptrdiff_t, N> const& arr, std::ptrdiff_t i) {
				return i < n - 1
					? sprout::fixed::detail::make_shuffle_indexes_1(
						n,
						sprout::random::next(rnd)(),
						sprout::fixed::swap_element(arr, arr.begin() + i, arr.begin() + sprout::random::result(rnd)),
						i + 1
						)
					: sprout::fixed::swap_element(arr, arr.begin() + i, arr.begin() + sprout::random::result(rnd))
					;
			}
			template<std::size_t N, typename UniformRandomNumberGenerator>
			inline SPROUT_CONSTEXPR sprout::array<std::ptrdiff_t, N>
			make_shuffle_indexes(std::ptrdiff_t n, UniformRandomNumberGenerator&& g) {
				return n > 1
					? sprout::fixed::detail::make_shuffle_indexes_1(
						n,
						SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION<std::ptrdiff_t>(0, n - 1)(
							SPROUT_FORWARD(UniformRandomNumberGenerator, g)
							),
						sprout::fixed::iota(sprout::pit<sprout::array<std::ptrdiff_t, N> >(), 0),
						0
						)
					: sprout::array<std::ptrdiff_t, N>{{}}
					;
			}
			template<typename Container, typename Shuffled, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
			shuffle_impl_1(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				Shuffled const& shuffled,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::remake<Container>(
					cont,
					sprout::size(cont),
					(Indexes >= offset && Indexes < offset + size
						? *sprout::next(sprout::begin(cont), shuffled[Indexes - offset])
						: *sprout::next(sprout::internal_begin(cont), Indexes)
						)...
					);
			}
			template<typename Container, typename UniformRandomNumberGenerator, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
			shuffle_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...> indexes,
				UniformRandomNumberGenerator&& g,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::fixed::detail::shuffle_impl_1(
					cont,
					indexes,
					sprout::fixed::detail::make_shuffle_indexes<sprout::container_traits<Container>::static_size>(
						size,
						SPROUT_FORWARD(UniformRandomNumberGenerator, g)
						),
					offset,
					size
					);
			}
		}	// namespace detail
		//
		// shuffle
		//
		template<typename Container, typename UniformRandomNumberGenerator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		shuffle(Container const& cont, UniformRandomNumberGenerator&& g) {
			return sprout::fixed::detail::shuffle_impl(
				cont,
				sprout::container_indexes<Container>::make(),
				SPROUT_FORWARD(UniformRandomNumberGenerator, g),
				sprout::internal_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::shuffle;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SHUFFLE_HPP
