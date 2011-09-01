#ifndef SPROUT_ALGORITHM_INFIT_NTH_ELEMENT_HPP
#define SPROUT_ALGORITHM_INFIT_NTH_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/nth_element.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace infit {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> nth_element_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::const_iterator nth,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::nth_element(cont, nth, comp),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), nth) + 1
					);
			}
		}	// namespace detail
		//
		// nth_element
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> nth_element(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator nth,
			Compare comp
			)
		{
			return sprout::infit::detail::nth_element_impl(cont, nth, comp, sprout::fixed_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> nth_element_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::const_iterator nth,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::nth_element(cont, nth),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), nth) + 1
					);
			}
		}	// namespace detail
		//
		// nth_element
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> nth_element(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator nth
			)
		{
			return sprout::infit::detail::nth_element_impl(cont, nth, sprout::fixed_begin_offset(cont));
		}
	}	// namespace infit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INFIT_NTH_ELEMENT_HPP
