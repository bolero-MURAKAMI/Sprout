#ifndef SPROUT_ALGORITHM_FIXED_MAKE_PARTIAL_HEAP_HPP
#define SPROUT_ALGORITHM_FIXED_MAKE_PARTIAL_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/algorithm/fixed/pop_heap.hpp>
#include <sprout/algorithm/fixed/make_heap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type make_partial_heap_impl_1(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::difference_type size,
				typename sprout::fixed_container_traits<Container>::difference_type middle_size,
				typename sprout::fixed_container_traits<Container>::difference_type n
				)
			{
				return n < size
					? comp(*sprout::next(sprout::fixed_begin(cont), offset + n), *sprout::next(sprout::fixed_begin(cont), offset))
						? sprout::fixed::detail::make_partial_heap_impl_1(
							sprout::fixed::detail::pop_heap_impl(
								sprout::fixed::swap_element(
									cont,
									sprout::next(sprout::fixed_begin(cont), offset + n),
									sprout::next(sprout::fixed_begin(cont), offset)
									),
								comp,
								offset,
								middle_size
								),
							comp,
							offset,
							size,
							middle_size,
							n + 1
							)
						: sprout::fixed::detail::make_partial_heap_impl_1(cont, comp, offset, size, middle_size, n + 1)
					: sprout::clone(cont)
					;
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type make_partial_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::difference_type size,
				typename sprout::fixed_container_traits<Container>::difference_type middle_size
				)
			{
				return sprout::fixed::detail::make_partial_heap_impl_1(
					sprout::fixed::detail::make_heap_impl(cont, comp, offset, middle_size),
					comp,
					offset,
					size,
					middle_size,
					middle_size
					);
			}
		}	// namespace detail
		//
		// make_partial_heap
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type make_partial_heap(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator middle,
			Compare comp
			)
		{
			return sprout::fixed::detail::make_partial_heap_impl(
				cont,
				comp,
				sprout::fixed_begin_offset(cont),
				sprout::size(cont),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), middle)
				);
		}
		//
		// make_partial_heap
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type make_partial_heap(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator middle
			)
		{
			return sprout::fixed::detail::make_partial_heap_impl(
				cont,
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::fixed_container_traits<Container>::value_type>(),
				sprout::fixed_begin_offset(cont),
				sprout::size(cont),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), middle)
				);
		}
	}	// namespace fixed

	using sprout::fixed::make_partial_heap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_MAKE_PARTIAL_HEAP_HPP
