#ifndef SPROUT_ALGORITHM_FIXED_NTH_ELEMENT_HPP
#define SPROUT_ALGORITHM_FIXED_NTH_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/algorithm/fixed/make_partial_heap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type nth_element_impl_1(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::difference_type nth_size
				)
			{
				return sprout::fixed::swap_element(
					cont,
					sprout::next(sprout::fixed_begin(cont), offset),
					sprout::next(sprout::fixed_begin(cont), offset + nth_size)
					);
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type nth_element_impl(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::difference_type size,
				typename sprout::fixed_container_traits<Container>::difference_type nth_size
				)
			{
				return sprout::fixed::detail::nth_element_impl_1(
					sprout::fixed::detail::make_partial_heap_impl(cont, comp, offset, size, nth_size + 1),
					offset,
					nth_size
					);
			}
		}	// namespace detail
		//
		// nth_element
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type nth_element(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator nth,
			Compare comp
			)
		{
			return sprout::fixed::detail::nth_element_impl(
				cont,
				comp,
				sprout::fixed_begin_offset(cont),
				sprout::size(cont),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), nth)
				);
		}
		//
		// nth_element
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type nth_element(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator nth
			)
		{
			return sprout::fixed::detail::nth_element_impl(
				cont,
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::fixed_container_traits<Container>::value_type>(),
				sprout::fixed_begin_offset(cont),
				sprout::size(cont),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), nth)
				);
		}
	}	// namespace fixed

	using sprout::fixed::nth_element;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_NTH_ELEMENT_HPP
