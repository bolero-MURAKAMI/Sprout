#ifndef SPROUT_ALGORITHM_FIXED_SORT_HEAP_HPP
#define SPROUT_ALGORITHM_FIXED_SORT_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/algorithm/fixed/pop_heap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort_heap_impl(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::difference_type size
				)
			{
				return size < 2
					? sprout::clone(cont)
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
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort_heap(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::fixed::detail::sort_heap_impl(
				cont,
				comp,
				sprout::fixed_begin_offset(cont),
				sprout::size(cont)
				);
		}
		//
		// sort_heap
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type sort_heap(
			Container const& cont
			)
		{
			return sprout::fixed::detail::sort_heap_impl(
				cont,
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::fixed_container_traits<Container>::value_type>(),
				sprout::fixed_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::sort_heap;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SORT_HEAP_HPP
