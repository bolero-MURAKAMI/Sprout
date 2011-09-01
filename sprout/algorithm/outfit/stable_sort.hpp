#ifndef SPROUT_ALGORITHM_OUTFIT_STABLE_SORT_HPP
#define SPROUT_ALGORITHM_OUTFIT_STABLE_SORT_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/stable_sort.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> stable_sort_impl(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::stable_sort(cont, comp),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// stable_sort
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> stable_sort(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::outfit::detail::stable_sort_impl(cont, comp, sprout::fixed_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> stable_sort_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::stable_sort(cont),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// stable_sort
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> stable_sort(
			Container const& cont
			)
		{
			return sprout::outfit::detail::stable_sort_impl(cont, sprout::fixed_begin_offset(cont));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_STABLE_SORT_HPP
