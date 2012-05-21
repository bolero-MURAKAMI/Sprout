#ifndef SPROUT_ALGORITHM_FIXED_MAKE_HEAP_HPP
#define SPROUT_ALGORITHM_FIXED_MAKE_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type make_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type n = 0,
				typename sprout::container_traits<Container>::difference_type l = 1,
				typename sprout::container_traits<Container>::difference_type r = 2
				);
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type make_heap_impl_1(
				Container const& cont,
				Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type n,
				typename sprout::container_traits<Container>::difference_type l,
				typename sprout::container_traits<Container>::difference_type r
				)
			{
				return comp(*sprout::next(sprout::internal_begin(cont), offset + l), *sprout::next(sprout::internal_begin(cont), offset + r))
					? comp(*sprout::next(sprout::internal_begin(cont), offset + n), *sprout::next(sprout::internal_begin(cont), offset + r))
						? sprout::fixed::detail::make_heap_impl(
							sprout::fixed::swap_element(
								cont,
								sprout::next(sprout::internal_begin(cont), offset + n),
								sprout::next(sprout::internal_begin(cont), offset + r)
								),
							comp,
							offset,
							size,
							r,
							r * 2 + 1,
							r * 2 + 2
							)
						: sprout::deep_copy(cont)
					: comp(*sprout::next(sprout::internal_begin(cont), offset + n), *sprout::next(sprout::internal_begin(cont), offset + l))
						? sprout::fixed::detail::make_heap_impl(
							sprout::fixed::swap_element(
								cont,
								sprout::next(sprout::internal_begin(cont), offset + n),
								sprout::next(sprout::internal_begin(cont), offset + l)
								),
							comp,
							offset,
							size,
							l,
							l * 2 + 1,
							l * 2 + 2
							)
						: sprout::deep_copy(cont)
					;
			}
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type make_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type n,
				typename sprout::container_traits<Container>::difference_type l,
				typename sprout::container_traits<Container>::difference_type r
				)
			{
				return r > size
					? sprout::deep_copy(cont)
					: r == size
						? comp(*sprout::next(sprout::internal_begin(cont), offset + n), *sprout::next(sprout::internal_begin(cont), offset + l))
							? sprout::fixed::swap_element(
								cont,
								sprout::next(sprout::internal_begin(cont), offset + n),
								sprout::next(sprout::internal_begin(cont), offset + l)
								)
							: sprout::deep_copy(cont)
						: sprout::fixed::detail::make_heap_impl_1(
							sprout::fixed::detail::make_heap_impl(
								sprout::fixed::detail::make_heap_impl(cont, comp, offset, size, l, l * 2 + 1, l * 2 + 2),
								comp,
								offset,
								size,
								r,
								r * 2 + 1,
								r * 2 + 2
								),
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
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type make_heap(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::fixed::detail::make_heap_impl(
				cont,
				comp,
				sprout::internal_begin_offset(cont),
				sprout::size(cont)
				);
		}
		//
		// make_heap
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type make_heap(
			Container const& cont
			)
		{
			return sprout::fixed::detail::make_heap_impl(
				cont,
				NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Container>::value_type>(),
				sprout::internal_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::make_heap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_MAKE_HEAP_HPP
