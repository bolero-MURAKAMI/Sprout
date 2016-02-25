/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_SORT_HEAP_HPP
#define SPROUT_ALGORITHM_FIXED_SORT_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/algorithm/fixed/pop_heap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
			sort_heap_impl(
				Container const& cont, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size
				)
			{
				return size < 2
					? sprout::deep_copy(cont)
					: sprout::fixed::detail::sort_heap_impl(
						sprout::fixed::detail::pop_heap_impl(
							sprout::fixed::swap_element(cont, sprout::begin(cont), sprout::next(sprout::begin(cont), size - 1)),
							comp,
							offset,
							size - 1
							),
						comp,
						offset,
						size - 1
						)
					;
			}
		}	// namespace detail
		//
		// sort_heap
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		sort_heap(Container const& cont, Compare comp) {
			return sprout::fixed::detail::sort_heap_impl(
				cont, comp,
				sprout::internal_begin_offset(cont),
				sprout::size(cont)
				);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		sort_heap(Container const& cont) {
			return sprout::fixed::detail::sort_heap_impl(
				cont, NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Container>::value_type>(),
				sprout::internal_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::sort_heap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SORT_HEAP_HPP
