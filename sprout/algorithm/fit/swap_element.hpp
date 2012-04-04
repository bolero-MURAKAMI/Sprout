#ifndef SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_HPP
#define SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/swap_element.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>


namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type swap_element_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::const_iterator pos1,
				typename sprout::container_traits<Container>::const_iterator pos2,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::swap_element(cont, pos1, pos2)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// swap_element
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type swap_element(
			Container const& cont,
			typename sprout::container_traits<Container>::const_iterator pos1,
			typename sprout::container_traits<Container>::const_iterator pos2
			)
		{
			return sprout::fit::detail::swap_element_impl(cont, pos1, pos2, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_HPP
