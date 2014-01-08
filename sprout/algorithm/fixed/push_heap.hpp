/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_PUSH_HEAP_HPP
#define SPROUT_ALGORITHM_FIXED_PUSH_HEAP_HPP

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
			push_heap_impl(
				Container const& cont, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type n
				)
			{
				return n != 0
					&& comp(
						*sprout::next(sprout::internal_begin(cont), offset + (n - 1) / 2),
						*sprout::next(sprout::internal_begin(cont), offset + n)
						)
					? sprout::fixed::detail::push_heap_impl(
						sprout::fixed::swap_element(
							cont,
							sprout::next(sprout::internal_begin(cont), offset + (n - 1) / 2),
							sprout::next(sprout::internal_begin(cont), offset + n)
							),
						comp,
						offset,
						(n - 1) / 2
						)
					: sprout::deep_copy(cont)
					;
			}
		}	// namespace detail
		//
		// push_heap
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		push_heap(Container const& cont, Compare comp) {
			return sprout::fixed::detail::push_heap_impl(
				cont, comp,
				sprout::internal_begin_offset(cont),
				sprout::size(cont) - 1
				);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		push_heap(Container const& cont) {
			return sprout::fixed::detail::push_heap_impl(
				cont, NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Container>::value_type>(),
				sprout::internal_begin_offset(cont),
				sprout::size(cont) - 1
				);
		}
	}	// namespace fixed

	using sprout::fixed::push_heap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_PUSH_HEAP_HPP
