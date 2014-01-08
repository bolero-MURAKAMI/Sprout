/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_BOZO_SORT_RESULT_HPP
#define SPROUT_ALGORITHM_FIXED_BOZO_SORT_RESULT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/utility/pair/access.hpp>
#include <sprout/algorithm/is_sorted.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/random_swap_result.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename ResultType, typename Compare, typename Difference>
			inline SPROUT_CONSTEXPR sprout::pair<ResultType, bool>
			bozo_sort_result_impl_1(
				sprout::pair<ResultType, bool> const& current,
				Compare comp, Difference n
				)
			{
				typedef sprout::pair<ResultType, bool> type;
			return current.second ? current
				: n == 1 ? sprout::is_sorted(sprout::begin(sprout::first(current.first)), sprout::end(sprout::first(current.first)), comp)
					? type(current.first, true)
					: type(sprout::fixed::random_swap_result(sprout::first(current.first), sprout::second(current.first)), false)
				: sprout::fixed::detail::bozo_sort_result_impl_1<ResultType>(
					sprout::fixed::detail::bozo_sort_result_impl_1<ResultType>(
						current,
						comp, n / 2
						),
					comp, n - n / 2
					)
				;
			}
			template<typename ResultType, typename Compare, typename Difference>
			inline SPROUT_CONSTEXPR sprout::pair<ResultType, bool>
			bozo_sort_result_impl(
				sprout::pair<ResultType, bool> const& current,
				Compare comp, Difference n
				)
			{
				return current.second ? current
					: sprout::fixed::detail::bozo_sort_result_impl<ResultType>(
						sprout::fixed::detail::bozo_sort_result_impl_1<ResultType>(
							current,
							comp, n
							),
						comp, n * 2
						)
					;
			}
			template<typename Container, typename UniformRandomNumberGenerator, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::shuffle<Container, UniformRandomNumberGenerator>::type
			bozo_sort_result(Container const& cont, UniformRandomNumberGenerator&& g, Compare comp) {
				typedef typename sprout::fixed::results::shuffle<Container, UniformRandomNumberGenerator>::type result_type;
				typedef sprout::pair<result_type, bool> type;
				return sprout::is_sorted(sprout::begin(cont), sprout::end(cont), comp)
					? result_type(sprout::deep_copy(cont), sprout::forward<UniformRandomNumberGenerator>(g))
					: sprout::fixed::detail::bozo_sort_result_impl<result_type>(
						type(sprout::fixed::random_swap_result(cont, sprout::forward<UniformRandomNumberGenerator>(g)), false),
						comp, static_cast<typename sprout::container_traits<Container>::difference_type>(1)
						).first
					;
			}
		}	// namespace detail
		//
		// bozo_sort_result
		//
		template<typename Container, typename UniformRandomNumberGenerator, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::shuffle<Container, UniformRandomNumberGenerator>::type
		bozo_sort_result(Container const& cont, UniformRandomNumberGenerator&& g, Compare comp) {
			return sprout::fixed::detail::bozo_sort_result(
				cont,
				sprout::forward<UniformRandomNumberGenerator>(g),
				comp
				);
		}
		template<typename Container, typename UniformRandomNumberGenerator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::shuffle<Container, UniformRandomNumberGenerator>::type
		bozo_sort_result(Container const& cont, UniformRandomNumberGenerator&& g) {
			return sprout::fixed::detail::bozo_sort_result(
				cont,
				sprout::forward<UniformRandomNumberGenerator>(g),
				NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Container>::value_type>()
				);
		}
	}	// namespace fixed

	using sprout::fixed::bozo_sort_result;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_BOZO_SORT_RESULT_HPP
