/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_MAKE_HEAP_HPP
#define SPROUT_ALGORITHM_FIXED_MAKE_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT
#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
#	include <sprout/workaround/recursive_function_template.hpp>
#endif

namespace sprout {
	namespace fixed {
		namespace detail {
#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
			template<int D = 16, typename Container, typename Compare, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			make_heap_impl(
				Container const& cont, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type n = 0,
				typename sprout::container_traits<Container>::difference_type l = 1,
				typename sprout::container_traits<Container>::difference_type r = 2
				);
			template<int D = 16, typename Container, typename Compare, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			make_heap_impl(
				Container const& cont, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type n = 0,
				typename sprout::container_traits<Container>::difference_type l = 1,
				typename sprout::container_traits<Container>::difference_type r = 2
				);
			template<int D, typename Container, typename Compare, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			make_heap_impl_1(
				Container const& cont, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type n,
				typename sprout::container_traits<Container>::difference_type l,
				typename sprout::container_traits<Container>::difference_type r
				)
			{
				return comp(*sprout::next(sprout::internal_begin(cont), offset + l), *sprout::next(sprout::internal_begin(cont), offset + r))
					? comp(*sprout::next(sprout::internal_begin(cont), offset + n), *sprout::next(sprout::internal_begin(cont), offset + r))
						? sprout::fixed::detail::make_heap_impl<D + 1>(
							sprout::fixed::swap_element(
								cont,
								sprout::next(sprout::internal_begin(cont), offset + n),
								sprout::next(sprout::internal_begin(cont), offset + r)
								),
							comp,
							offset, size, r, r * 2 + 1, r * 2 + 2
							)
						: sprout::deep_copy(cont)
					: comp(*sprout::next(sprout::internal_begin(cont), offset + n), *sprout::next(sprout::internal_begin(cont), offset + l))
						? sprout::fixed::detail::make_heap_impl<D + 1>(
							sprout::fixed::swap_element(
								cont,
								sprout::next(sprout::internal_begin(cont), offset + n),
								sprout::next(sprout::internal_begin(cont), offset + l)
								),
							comp,
							offset, size, l, l * 2 + 1, l * 2 + 2
							)
						: sprout::deep_copy(cont)
					;
			}
			template<int D, typename Container, typename Compare, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			make_heap_impl_1(
				Container const&, Compare,
				typename sprout::container_traits<Container>::difference_type,
				typename sprout::container_traits<Container>::difference_type,
				typename sprout::container_traits<Container>::difference_type,
				typename sprout::container_traits<Container>::difference_type,
				typename sprout::container_traits<Container>::difference_type
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Container, typename Compare, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE_DECL(D)>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			make_heap_impl(
				Container const& cont, Compare comp,
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
						: sprout::fixed::detail::make_heap_impl_1<D + 1>(
							sprout::fixed::detail::make_heap_impl<D + 1>(
								sprout::fixed::detail::make_heap_impl<D + 1>(cont, comp, offset, size, l, l * 2 + 1, l * 2 + 2),
								comp,
								offset, size,
								r, r * 2 + 1, r * 2 + 2
								),
							comp,
							offset, size, n, l, r
							)
					;
			}
			template<int D, typename Container, typename Compare, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK_DECL(D)>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			make_heap_impl(
				Container const&, Compare,
				typename sprout::container_traits<Container>::difference_type,
				typename sprout::container_traits<Container>::difference_type,
				typename sprout::container_traits<Container>::difference_type,
				typename sprout::container_traits<Container>::difference_type,
				typename sprout::container_traits<Container>::difference_type
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
#else
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			make_heap_impl(
				Container const& cont, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type n = 0,
				typename sprout::container_traits<Container>::difference_type l = 1,
				typename sprout::container_traits<Container>::difference_type r = 2
				);
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			make_heap_impl_1(
				Container const& cont, Compare comp,
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
							offset, size, r, r * 2 + 1, r * 2 + 2
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
							offset, size, l, l * 2 + 1, l * 2 + 2
							)
						: sprout::deep_copy(cont)
					;
			}
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			make_heap_impl(
				Container const& cont, Compare comp,
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
								offset, size,
								r, r * 2 + 1, r * 2 + 2
								),
							comp,
							offset, size, n, l, r
							)
					;
			}
#endif
		}	// namespace detail
		//
		// make_heap
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		make_heap(Container const& cont, Compare comp) {
			return sprout::fixed::detail::make_heap_impl(
				cont, comp,
				sprout::internal_begin_offset(cont),
				sprout::size(cont)
				);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		make_heap(Container const& cont) {
			return sprout::fixed::detail::make_heap_impl(
				cont, NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Container>::value_type>(),
				sprout::internal_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::make_heap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_MAKE_HEAP_HPP
