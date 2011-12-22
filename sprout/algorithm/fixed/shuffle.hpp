#ifndef SPROUT_ALGORITHM_FIXED_SHUFFLE_HPP
#define SPROUT_ALGORITHM_FIXED_SHUFFLE_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/array.hpp>
#include <sprout/pit.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/numeric/fixed/iota.hpp>
#include <sprout/random/uniform_int_distribution.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<std::size_t N, typename Random>
			SPROUT_CONSTEXPR inline sprout::array<std::ptrdiff_t, N> make_shuffle_indexes_1(
				std::ptrdiff_t n,
				Random const& rnd,
				sprout::array<std::ptrdiff_t, N> const& arr,
				std::ptrdiff_t i
				)
			{
				return i < n - 1
					? sprout::fixed::detail::make_shuffle_indexes_1(
						n,
						rnd(),
						sprout::fixed::swap_element(arr, arr.begin() + i, arr.begin() + rnd.result()),
						i + 1
						)
					: sprout::fixed::swap_element(arr, arr.begin() + i, arr.begin() + rnd.result())
					;
			}
			template<std::size_t N, typename UniformRandomNumberGenerator>
			SPROUT_CONSTEXPR inline sprout::array<std::ptrdiff_t, N> make_shuffle_indexes(
				std::ptrdiff_t n,
				UniformRandomNumberGenerator&& g
				)
			{

				return n > 0
					? sprout::fixed::detail::make_shuffle_indexes_1(
						n,
						sprout::random::uniform_int_distribution<std::ptrdiff_t>(0, n - 1)(sprout::forward<UniformRandomNumberGenerator>(g)),
						sprout::fixed::iota(sprout::pit<sprout::array<std::ptrdiff_t, N> >(), 0),
						0
						)
					: sprout::array<std::ptrdiff_t, N>{{}}
					;
			}
			template<typename Container, typename Shuffled, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type shuffle_impl_1(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				Shuffled const& shuffled,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::size_type size
				)
			{
				return sprout::remake_clone<Container>(
					cont,
					sprout::size(cont),
					(Indexes >= offset && Indexes < offset + size
						? *sprout::next(sprout::begin(cont), shuffled[Indexes - offset])
						: *sprout::next(sprout::fixed_begin(cont), Indexes)
						)...
					);
			}
			template<typename Container, typename UniformRandomNumberGenerator, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type shuffle_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...> indexes,
				UniformRandomNumberGenerator&& g,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::size_type size
				)
			{
				return sprout::fixed::detail::shuffle_impl_1(
					cont,
					indexes,
					sprout::fixed::detail::make_shuffle_indexes<sprout::fixed_container_traits<Container>::fixed_size>(
						size,
						sprout::forward<UniformRandomNumberGenerator>(g)
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
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type shuffle(
			Container const& cont,
			UniformRandomNumberGenerator&& g
			)
		{
			return sprout::fixed::detail::shuffle_impl(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<Container>::fixed_size>::type(),
				sprout::forward<UniformRandomNumberGenerator>(g),
				sprout::fixed_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::shuffle;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SHUFFLE_HPP
