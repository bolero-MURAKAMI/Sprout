/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_SHUFFLE_RESULT_HPP
#define SPROUT_ALGORITHM_FIXED_SHUFFLE_RESULT_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/array/array.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/utility/pair/access.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/numeric/fixed/iota.hpp>
#include <sprout/random/results.hpp>
#include <sprout/workaround/detail/uniform_int_distribution.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename UniformRandomNumberGenerator, std::size_t N, typename Random>
			inline SPROUT_CONSTEXPR sprout::pair<sprout::array<std::ptrdiff_t, N>, typename std::decay<UniformRandomNumberGenerator>::type>
			make_shuffle_result_indexes_1(std::ptrdiff_t n, Random const& rnd, sprout::array<std::ptrdiff_t, N> const& arr, std::ptrdiff_t i) {
				typedef sprout::pair<sprout::array<std::ptrdiff_t, N>, typename std::decay<UniformRandomNumberGenerator>::type> result_type;
				return i < n - 1
					? sprout::fixed::detail::make_shuffle_result_indexes_1<UniformRandomNumberGenerator>(
						n,
						sprout::random::next(rnd)(),
						sprout::fixed::swap_element(arr, arr.begin() + i, arr.begin() + sprout::random::result(rnd)),
						i + 1
						)
					: result_type(
						sprout::fixed::swap_element(arr, arr.begin() + i, arr.begin() + sprout::random::result(rnd)),
						sprout::random::next(rnd).engine()
						)
					;
			}
			template<std::size_t N, typename UniformRandomNumberGenerator>
			inline SPROUT_CONSTEXPR sprout::pair<sprout::array<std::ptrdiff_t, N>, typename std::decay<UniformRandomNumberGenerator>::type>
			make_shuffle_result_indexes(std::ptrdiff_t n, UniformRandomNumberGenerator&& g) {
				typedef sprout::pair<sprout::array<std::ptrdiff_t, N>, typename std::decay<UniformRandomNumberGenerator>::type> result_type;
				return n > 1
					? sprout::fixed::detail::make_shuffle_result_indexes_1<UniformRandomNumberGenerator>(
						n,
						SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION<std::ptrdiff_t>(0, n - 1)(
							sprout::forward<UniformRandomNumberGenerator>(g)
							),
						sprout::fixed::iota(sprout::pit<sprout::array<std::ptrdiff_t, N> >(), 0),
						0
						)
					: result_type(
						sprout::array<std::ptrdiff_t, N>{{}},
						sprout::forward<UniformRandomNumberGenerator>(g)
						)
					;
			}
			template<typename UniformRandomNumberGenerator, typename Container, typename Shuffled, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::shuffle<Container, UniformRandomNumberGenerator>::type
			shuffle_result_impl_1(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				Shuffled const& shuffled,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				typedef typename sprout::fixed::results::shuffle<Container, UniformRandomNumberGenerator>::type result_type;
				return result_type(
					sprout::remake<Container>(
						cont,
						sprout::size(cont),
						(Indexes >= offset && Indexes < offset + size
							? *sprout::next(sprout::begin(cont), sprout::first(shuffled)[Indexes - offset])
							: *sprout::next(sprout::internal_begin(cont), Indexes)
							)...
						),
						sprout::second(shuffled)
					);
			}
			template<typename Container, typename UniformRandomNumberGenerator, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::shuffle<Container, UniformRandomNumberGenerator>::type
			shuffle_result_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...> indexes,
				UniformRandomNumberGenerator&& g,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::fixed::detail::shuffle_result_impl_1<UniformRandomNumberGenerator>(
					cont,
					indexes,
					sprout::fixed::detail::make_shuffle_result_indexes<sprout::container_traits<Container>::static_size>(
						size,
						sprout::forward<UniformRandomNumberGenerator>(g)
						),
					offset,
					size
					);
			}
		}	// namespace detail
		//
		// shuffle_result
		//
		template<typename Container, typename UniformRandomNumberGenerator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::shuffle<Container, UniformRandomNumberGenerator>::type
		shuffle_result(Container const& cont, UniformRandomNumberGenerator&& g) {
			return sprout::fixed::detail::shuffle_result_impl(
				cont,
				sprout::container_indexes<Container>::make(),
				sprout::forward<UniformRandomNumberGenerator>(g),
				sprout::internal_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::shuffle_result;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SHUFFLE_RESULT_HPP
