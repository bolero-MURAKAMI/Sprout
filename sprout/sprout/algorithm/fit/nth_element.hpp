#ifndef SPROUT_ALGORITHM_FIT_NTH_ELEMENT_HPP
#define SPROUT_ALGORITHM_FIT_NTH_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/nth_element.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type nth_element_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::const_iterator nth,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::nth_element(cont, nth, comp)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), nth) + 1
					);
			}
		}	// namespace detail
		//
		// nth_element
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type nth_element(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator nth,
			Compare comp
			)
		{
			return sprout::fit::detail::nth_element_impl(cont, nth, comp, sprout::fixed_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type nth_element_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::const_iterator nth,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::nth_element(cont, nth)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), nth) + 1
					);
			}
		}	// namespace detail
		//
		// nth_element
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type nth_element(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator nth
			)
		{
			return sprout::fit::detail::nth_element_impl(cont, nth, sprout::fixed_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_NTH_ELEMENT_HPP
