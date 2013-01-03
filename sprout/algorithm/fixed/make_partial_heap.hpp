#ifndef SPROUT_ALGORITHM_FIXED_MAKE_PARTIAL_HEAP_HPP
#define SPROUT_ALGORITHM_FIXED_MAKE_PARTIAL_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/algorithm/fixed/pop_heap.hpp>
#include <sprout/algorithm/fixed/make_heap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			make_partial_heap_impl_1(
				Container const& cont, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type middle_size,
				typename sprout::container_traits<Container>::difference_type n
				)
			{
				return n < size
					? comp(*sprout::next(sprout::internal_begin(cont), offset + n), *sprout::next(sprout::internal_begin(cont), offset))
						? sprout::fixed::detail::make_partial_heap_impl_1(
							sprout::fixed::detail::pop_heap_impl(
								sprout::fixed::swap_element(
									cont,
									sprout::next(sprout::internal_begin(cont), offset + n),
									sprout::next(sprout::internal_begin(cont), offset)
									),
								comp,
								offset, middle_size
								),
							comp,
							offset, size, middle_size, n + 1
							)
						: sprout::fixed::detail::make_partial_heap_impl_1(cont, comp, offset, size, middle_size, n + 1)
					: sprout::deep_copy(cont)
					;
			}
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			make_partial_heap_impl(
				Container const& cont, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type middle_size
				)
			{
				return sprout::fixed::detail::make_partial_heap_impl_1(
					sprout::fixed::detail::make_heap_impl(cont, comp, offset, middle_size), comp,
					offset, size, middle_size, middle_size
					);
			}
		}	// namespace detail
		//
		// make_partial_heap
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		make_partial_heap(Container const& cont, typename sprout::container_traits<Container>::const_iterator middle, Compare comp) {
			return sprout::fixed::detail::make_partial_heap_impl(
				cont, comp,
				sprout::internal_begin_offset(cont),
				sprout::size(cont),
				sprout::distance(sprout::begin(cont), middle)
				);
		}
		//
		// make_partial_heap
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		make_partial_heap(Container const& cont, typename sprout::container_traits<Container>::const_iterator middle) {
			return sprout::fixed::detail::make_partial_heap_impl(
				cont, NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Container>::value_type>(),
				sprout::internal_begin_offset(cont),
				sprout::size(cont),
				sprout::distance(sprout::begin(cont), middle)
				);
		}
	}	// namespace fixed

	using sprout::fixed::make_partial_heap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_MAKE_PARTIAL_HEAP_HPP
