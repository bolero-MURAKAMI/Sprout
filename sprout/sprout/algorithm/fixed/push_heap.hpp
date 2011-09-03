#ifndef SPROUT_ALGORITHM_FIXED_PUSH_HEAP_HPP
#define SPROUT_ALGORITHM_FIXED_PUSH_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type push_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::difference_type n
				)
			{
				return n != 0 && comp(*(sprout::fixed_begin(cont) + offset + (n - 1) / 2), *(sprout::fixed_begin(cont) + offset + n))
					? sprout::fixed::detail::push_heap_impl(
						sprout::fixed::swap_element(cont, sprout::fixed_begin(cont) + offset + (n - 1) / 2, sprout::fixed_begin(cont) + offset + n),
						comp,
						offset,
						(n - 1) / 2
						)
					: sprout::clone(cont)
					;
			}
		}	// namespace detail
		//
		// push_heap
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type push_heap(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::fixed::detail::push_heap_impl(
				cont,
				comp,
				sprout::fixed_begin_offset(cont),
				sprout::size(cont) - 1
				);
		}
		//
		// push_heap
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type push_heap(
			Container const& cont
			)
		{
			return sprout::fixed::detail::push_heap_impl(
				cont,
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::fixed_container_traits<Container>::value_type>(),
				sprout::fixed_begin_offset(cont),
				sprout::size(cont) - 1
				);
		}
	}	// namespace fixed

	using sprout::fixed::push_heap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_PUSH_HEAP_HPP
