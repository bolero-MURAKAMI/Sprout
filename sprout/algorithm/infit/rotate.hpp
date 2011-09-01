#ifndef SPROUT_ALGORITHM_INFIT_ROTATE_HPP
#define SPROUT_ALGORITHM_INFIT_ROTATE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/rotate.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace infit {
		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> rotate_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::const_iterator middle,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::rotate(cont, middle),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// rotate
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> rotate(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator middle
			)
		{
			return sprout::infit::detail::rotate_impl(cont, middle, sprout::fixed_begin_offset(cont));
		}
	}	// namespace infit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INFIT_ROTATE_HPP
