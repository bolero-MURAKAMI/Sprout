#ifndef SPROUT_ALGORITHM_FIXED_SHUFFLE_RESULT_HPP
#define SPROUT_ALGORITHM_FIXED_SHUFFLE_RESULT_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/array.hpp>
#include <sprout/pit.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/numeric/fixed/iota.hpp>
#include <sprout/random/uniform_int_distribution.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename UniformRandomNumberGenerator, std::size_t N, typename Random>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				sprout::array<std::ptrdiff_t, N>,
				typename std::decay<UniformRandomNumberGenerator>::type
			> make_shuffle_result_indexes_1(
				std::ptrdiff_t n,
				Random const& rnd,
				sprout::array<std::ptrdiff_t, N> const& arr,
				std::ptrdiff_t i
				)
			{
				typedef sprout::tuples::tuple<
					sprout::array<std::ptrdiff_t, N>,
					typename std::decay<UniformRandomNumberGenerator>::type
				> result_type;
				return i < n - 1
					? sprout::fixed::detail::make_shuffle_result_indexes_1<UniformRandomNumberGenerator>(
						n,
						rnd(),
						sprout::fixed::swap_element(arr, arr.begin() + i, arr.begin() + rnd.result()),
						i + 1
						)
					: result_type(
						sprout::fixed::swap_element(arr, arr.begin() + i, arr.begin() + rnd.result()),
						rnd.engine()
						)
					;
			}
			template<std::size_t N, typename UniformRandomNumberGenerator>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				sprout::array<std::ptrdiff_t, N>,
				typename std::decay<UniformRandomNumberGenerator>::type
			> make_shuffle_result_indexes(
				std::ptrdiff_t n,
				UniformRandomNumberGenerator&& g
				)
			{
				typedef sprout::tuples::tuple<
					sprout::array<std::ptrdiff_t, N>,
					typename std::decay<UniformRandomNumberGenerator>::type
				> result_type;
				return n > 0
					? sprout::fixed::detail::make_shuffle_result_indexes_1<UniformRandomNumberGenerator>(
						n,
						sprout::random::uniform_int_distribution<std::ptrdiff_t>(0, n - 1)(sprout::forward<UniformRandomNumberGenerator>(g)),
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
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				typename sprout::fixed::result_of::algorithm<Container>::type,
				typename std::decay<UniformRandomNumberGenerator>::type
			> shuffle_result_impl_1(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				Shuffled const& shuffled,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				typedef sprout::tuples::tuple<
					typename sprout::fixed::result_of::algorithm<Container>::type,
					typename std::decay<UniformRandomNumberGenerator>::type
				> result_type;
				return result_type(
					sprout::remake<Container>(
						cont,
						sprout::size(cont),
						(Indexes >= offset && Indexes < offset + size
							? *sprout::next(sprout::begin(cont), sprout::tuples::get<0>(shuffled)[Indexes - offset])
							: *sprout::next(sprout::internal_begin(cont), Indexes)
							)...
						),
						sprout::tuples::get<1>(shuffled)
					);
			}
			template<typename Container, typename UniformRandomNumberGenerator, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				typename sprout::fixed::result_of::algorithm<Container>::type,
				typename std::decay<UniformRandomNumberGenerator>::type
			> shuffle_result_impl(
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
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<
			typename sprout::fixed::result_of::algorithm<Container>::type,
			typename std::decay<UniformRandomNumberGenerator>::type
		> shuffle_result(
			Container const& cont,
			UniformRandomNumberGenerator&& g
			)
		{
			return sprout::fixed::detail::shuffle_result_impl(
				cont,
				sprout::index_range<0, sprout::container_traits<Container>::static_size>::make(),
				sprout::forward<UniformRandomNumberGenerator>(g),
				sprout::internal_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::shuffle_result;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SHUFFLE_RESULT_HPP
