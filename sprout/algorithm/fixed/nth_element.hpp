#ifndef SPROUT_ALGORITHM_FIXED_NTH_ELEMENT_HPP
#define SPROUT_ALGORITHM_FIXED_NTH_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/algorithm/fixed/make_partial_heap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type nth_element_impl_1(
				Container const& cont,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type nth_size
				)
			{
				return sprout::fixed::swap_element(
					cont,
					sprout::next(sprout::internal_begin(cont), offset),
					sprout::next(sprout::internal_begin(cont), offset + nth_size)
					);
			}
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type nth_element_impl(
				Container const& cont,
				Compare comp,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::difference_type size,
				typename sprout::container_traits<Container>::difference_type nth_size
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
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type nth_element(
			Container const& cont,
			typename sprout::container_traits<Container>::const_iterator nth,
			Compare comp
			)
		{
			return sprout::fixed::detail::nth_element_impl(
				cont,
				comp,
				sprout::internal_begin_offset(cont),
				sprout::size(cont),
				NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::begin(cont), nth)
				);
		}
		//
		// nth_element
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type nth_element(
			Container const& cont,
			typename sprout::container_traits<Container>::const_iterator nth
			)
		{
			return sprout::fixed::detail::nth_element_impl(
				cont,
				NS_SSCRISK_CEL_OR_SPROUT::less<typename sprout::container_traits<Container>::value_type>(),
				sprout::internal_begin_offset(cont),
				sprout::size(cont),
				NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::begin(cont), nth)
				);
		}
	}	// namespace fixed

	using sprout::fixed::nth_element;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_NTH_ELEMENT_HPP
