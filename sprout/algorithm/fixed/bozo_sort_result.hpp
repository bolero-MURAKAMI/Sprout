#ifndef SPROUT_ALGORITHM_FIXED_BOZO_SORT_RESULT_HPP
#define SPROUT_ALGORITHM_FIXED_BOZO_SORT_RESULT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/random_swap_result.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename UniformRandomNumberGenerator, typename Shuffled, typename Compare>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				typename sprout::fixed::result_of::algorithm<Container>::type,
				typename std::decay<UniformRandomNumberGenerator>::type
			> bozo_sort_result_impl_1(
				Shuffled const& shuffled,
				Compare comp
				)
			{
				return NS_SSCRISK_CEL_OR_SPROUT::is_sorted(
					sprout::begin(sprout::tuples::get<0>(shuffled)),
					sprout::end(sprout::tuples::get<0>(shuffled)),
					comp
					)
					? shuffled
					: sprout::fixed::detail::bozo_sort_result_impl_1<Container, UniformRandomNumberGenerator>(
						sprout::fixed::random_swap_result(
							sprout::tuples::get<0>(shuffled),
							sprout::tuples::get<1>(shuffled)
							),
						comp
						)
					;
			}
			template<typename Container, typename UniformRandomNumberGenerator, typename Compare>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<
				typename sprout::fixed::result_of::algorithm<Container>::type,
				typename std::decay<UniformRandomNumberGenerator>::type
			> bozo_sort_result_impl(
				Container const& cont,
				UniformRandomNumberGenerator&& g,
				Compare comp
				)
			{
				typedef sprout::tuples::tuple<
					typename sprout::fixed::result_of::algorithm<Container>::type,
					typename std::decay<UniformRandomNumberGenerator>::type
				> result_type;
				return NS_SSCRISK_CEL_OR_SPROUT::is_sorted(
					sprout::begin(cont),
					sprout::end(cont),
					comp
					)
					? result_type(
						sprout::deep_copy(cont),
						sprout::forward<UniformRandomNumberGenerator>(g)
						)
					: sprout::fixed::detail::bozo_sort_result_impl_1<Container, UniformRandomNumberGenerator>(
						sprout::fixed::random_swap_result(
							cont,
							sprout::forward<UniformRandomNumberGenerator>(g)
							),
						comp
						)
					;
			}
		}	// namespace detail
		//
		// bozo_sort_result
		//
		template<typename Container, typename UniformRandomNumberGenerator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<
			typename sprout::fixed::result_of::algorithm<Container>::type,
			typename std::decay<UniformRandomNumberGenerator>::type
		> bozo_sort_result(
			Container const& cont,
			UniformRandomNumberGenerator&& g,
			Compare comp
			)
		{
			return sprout::fixed::detail::bozo_sort_result_impl(
				cont,
				sprout::forward<UniformRandomNumberGenerator>(g),
				comp
				);
		}
		//
		// bozo_sort_result
		//
		template<typename Container, typename UniformRandomNumberGenerator>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<
			typename sprout::fixed::result_of::algorithm<Container>::type,
			typename std::decay<UniformRandomNumberGenerator>::type
		> bozo_sort_result(
			Container const& cont,
			UniformRandomNumberGenerator&& g
			)
		{
			return sprout::fixed::detail::bozo_sort_result_impl(
				cont,
				sprout::forward<UniformRandomNumberGenerator>(g),
				NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Container>::value_type>()
				);
		}
	}	// namespace fixed

	using sprout::fixed::bozo_sort_result;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_BOZO_SORT_RESULT_HPP
