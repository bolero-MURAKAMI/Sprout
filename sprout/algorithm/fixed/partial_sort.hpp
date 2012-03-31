#ifndef SPROUT_ALGORITHM_FIXED_PARTIAL_SORT_HPP
#define SPROUT_ALGORITHM_FIXED_PARTIAL_SORT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/make_partial_heap.hpp>
#include <sprout/algorithm/fixed/sort_heap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type partial_sort_impl(
				Container const& cont,
				Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type middle_size
				)
			{
				return sprout::fixed::detail::sort_heap_impl(
					sprout::fixed::detail::make_partial_heap_impl(cont, comp, offset, size, middle_size),
					comp,
					offset,
					middle_size
					);
			}
		}	// namespace detail
		//
		// partial_sort
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type partial_sort(
			Container const& cont,
			typename sprout::container_traits<Container>::const_iterator middle,
			Compare comp
			)
		{
			return sprout::fixed::detail::partial_sort_impl(
				cont,
				comp,
				sprout::internal_begin_offset(cont),
				sprout::size(cont),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), middle)
				);
		}
		//
		// partial_sort
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type partial_sort(
			Container const& cont,
			typename sprout::container_traits<Container>::const_iterator middle
			)
		{
			return sprout::fixed::detail::partial_sort_impl(
				cont,
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::container_traits<Container>::value_type>(),
				sprout::internal_begin_offset(cont),
				sprout::size(cont),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), middle)
				);
		}
	}	// namespace fixed

	using sprout::fixed::partial_sort;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_PARTIAL_SORT_HPP
