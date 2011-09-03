#ifndef SPROUT_ALGORITHM_FIXED_MAKE_HEAP_HPP
#define SPROUT_ALGORITHM_FIXED_MAKE_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type make_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::difference_type size,
				typename sprout::fixed_container_traits<Container>::difference_type n = 0,
				typename sprout::fixed_container_traits<Container>::difference_type l = 1,
				typename sprout::fixed_container_traits<Container>::difference_type r = 2
				);
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type make_heap_impl_1(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::difference_type size,
				typename sprout::fixed_container_traits<Container>::difference_type n,
				typename sprout::fixed_container_traits<Container>::difference_type l,
				typename sprout::fixed_container_traits<Container>::difference_type r
				)
			{
				return comp(*(sprout::fixed_begin(cont) + offset + l), *(sprout::fixed_begin(cont) + offset + r))
					? comp(*(sprout::fixed_begin(cont) + offset + n), *(sprout::fixed_begin(cont) + offset + r))
						? sprout::fixed::detail::make_heap_impl(
							sprout::fixed::swap_element(cont, sprout::fixed_begin(cont) + offset + n, sprout::fixed_begin(cont) + offset + r),
							comp,
							offset,
							size,
							r,
							r * 2 + 1,
							r * 2 + 2
							)
						: sprout::clone(cont)
					: comp(*(sprout::fixed_begin(cont) + offset + n), *(sprout::fixed_begin(cont) + offset + l))
						? sprout::fixed::detail::make_heap_impl(
							sprout::fixed::swap_element(cont, sprout::fixed_begin(cont) + offset + n, sprout::fixed_begin(cont) + offset + l),
							comp,
							offset,
							size,
							l,
							l * 2 + 1,
							l * 2 + 2
							)
						: sprout::clone(cont)
					;
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type make_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::difference_type size,
				typename sprout::fixed_container_traits<Container>::difference_type n,
				typename sprout::fixed_container_traits<Container>::difference_type l,
				typename sprout::fixed_container_traits<Container>::difference_type r
				)
			{
				return r > size
					? sprout::clone(cont)
					: r == size
						? comp(*(sprout::fixed_begin(cont) + offset + n), *(sprout::fixed_begin(cont) + offset + l))
							? sprout::fixed::swap_element(cont, sprout::fixed_begin(cont) + offset + n, sprout::fixed_begin(cont) + offset + l)
							: sprout::clone(cont)
						: sprout::fixed::detail::make_heap_impl_1(
							sprout::fixed::detail::make_heap_impl(sprout::fixed::detail::make_heap_impl(cont, comp, offset, size, l, l * 2 + 1, l * 2 + 2), comp, offset, size, r, r * 2 + 1, r * 2 + 2),
							comp,
							offset,
							size,
							n,
							l,
							r
							)
					;
			}
		}	// namespace detail
		//
		// make_heap
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type make_heap(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::fixed::detail::make_heap_impl(
				cont,
				comp,
				sprout::fixed_begin_offset(cont),
				sprout::size(cont)
				);
		}
		//
		// make_heap
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type make_heap(
			Container const& cont
			)
		{
			return sprout::fixed::detail::make_heap_impl(
				cont,
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::fixed_container_traits<Container>::value_type>(),
				sprout::fixed_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::make_heap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_MAKE_HEAP_HPP
