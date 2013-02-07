#ifndef SPROUT_ALGORITHM_FIT_BOZO_SORT_HPP
#define SPROUT_ALGORITHM_FIT_BOZO_SORT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/bozo_sort.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename UniformRandomNumberGenerator, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			bozo_sort_impl(
				Container const& cont, UniformRandomNumberGenerator&& g, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::bozo_sort(cont, sprout::forward<UniformRandomNumberGenerator>(g), comp)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// bozo_sort
		//
		template<typename Container, typename UniformRandomNumberGenerator, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		bozo_sort(Container const& cont, UniformRandomNumberGenerator&& g, Compare comp) {
			return sprout::fit::detail::bozo_sort_impl(
				cont, sprout::forward<UniformRandomNumberGenerator>(g), comp,
				sprout::internal_begin_offset(cont)
				);
		}

		namespace detail {
			template<typename Container, typename UniformRandomNumberGenerator>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			bozo_sort_impl(
				Container const& cont, UniformRandomNumberGenerator&& g,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::bozo_sort(cont, sprout::forward<UniformRandomNumberGenerator>(g))),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// bozo_sort
		//
		template<typename Container, typename UniformRandomNumberGenerator>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		bozo_sort(Container const& cont, UniformRandomNumberGenerator&& g) {
			return sprout::fit::detail::bozo_sort_impl(
				cont, sprout::forward<UniformRandomNumberGenerator>(g),
				sprout::internal_begin_offset(cont)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_BOZO_SORT_HPP
