#ifndef SPROUT_ALGORITHM_OUTFIT_SWAP_ELEMENT_HPP
#define SPROUT_ALGORITHM_OUTFIT_SWAP_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> swap_element_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::const_iterator pos1,
				typename sprout::fixed_container_traits<Container>::const_iterator pos2,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::swap_element(cont, pos1, pos2),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// swap_element
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> swap_element(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator pos1,
			typename sprout::fixed_container_traits<Container>::const_iterator pos2
			)
		{
			return sprout::outfit::detail::swap_element_impl(cont, pos1, pos2, sprout::fixed_begin_offset(cont));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_SWAP_ELEMENT_HPP
