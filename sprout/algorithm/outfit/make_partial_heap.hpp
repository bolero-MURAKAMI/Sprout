#ifndef SPROUT_ALGORITHM_OUTFIT_MAKE_PARTIAL_HEAP_HPP
#define SPROUT_ALGORITHM_OUTFIT_MAKE_PARTIAL_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/make_partial_heap.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> make_partial_heap_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::const_iterator middle,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::make_partial_heap(cont, middle, comp),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// make_partial_heap
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> make_partial_heap(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator middle,
			Compare comp
			)
		{
			return sprout::outfit::detail::make_partial_heap_impl(cont, middle, comp, sprout::fixed_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> make_partial_heap_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::const_iterator middle,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::make_partial_heap(cont, middle),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// make_partial_heap
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> make_partial_heap(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator middle
			)
		{
			return sprout::outfit::detail::make_partial_heap_impl(cont, middle, sprout::fixed_begin_offset(cont));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_MAKE_PARTIAL_HEAP_HPP
