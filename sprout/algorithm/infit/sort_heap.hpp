#ifndef SPROUT_ALGORITHM_INFIT_SORT_HEAP_HPP
#define SPROUT_ALGORITHM_INFIT_SORT_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/sort_heap.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace infit {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> sort_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::sort_heap(cont, comp),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// sort_heap
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> sort_heap(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::infit::detail::sort_heap_impl(cont, comp, sprout::fixed_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> sort_heap_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::sort_heap(cont),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// sort_heap
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> sort_heap(
			Container const& cont
			)
		{
			return sprout::infit::detail::sort_heap_impl(cont, sprout::fixed_begin_offset(cont));
		}
	}	// namespace infit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INFIT_SORT_HEAP_HPP
