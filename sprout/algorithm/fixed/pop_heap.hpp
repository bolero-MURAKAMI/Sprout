/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_POP_HEAP_HPP
#define SPROUT_ALGORITHM_FIXED_POP_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
			pop_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type n = 0,
				typename sprout::container_traits<Container>::difference_type l = 1,
				typename sprout::container_traits<Container>::difference_type r = 2
				)
			{
				return r < size
					&& comp(*sprout::next(sprout::internal_begin(cont), offset + l), *sprout::next(sprout::internal_begin(cont), offset + r))
					? comp(*sprout::next(sprout::internal_begin(cont), offset + n), *sprout::next(sprout::internal_begin(cont), offset + r))
						? sprout::fixed::detail::pop_heap_impl(
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
					: l < size
						? comp(*sprout::next(sprout::internal_begin(cont), offset + n), *sprout::next(sprout::internal_begin(cont), offset + l))
							? sprout::fixed::detail::pop_heap_impl(
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
						: sprout::deep_copy(cont)
					;
			}
		}	// namespace detail
		//
		// pop_heap
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		pop_heap(Container const& cont, Compare comp) {
			return sprout::fixed::detail::pop_heap_impl(
				sprout::fixed::swap_element(cont, sprout::begin(cont), sprout::end(cont) - 1),
				comp,
				sprout::internal_begin_offset(cont),
				sprout::size(cont) - 1
				);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		pop_heap(Container const& cont) {
			return sprout::fixed::detail::pop_heap_impl(
				sprout::fixed::swap_element(cont, sprout::begin(cont), sprout::end(cont) - 1),
				NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Container>::value_type>(),
				sprout::internal_begin_offset(cont),
				sprout::size(cont) - 1
				);
		}
	}	// namespace fixed

	using sprout::fixed::pop_heap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_POP_HEAP_HPP
