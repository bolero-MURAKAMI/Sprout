#ifndef SPROUT_ALGORITHM_INFIT_REVERSE_HPP
#define SPROUT_ALGORITHM_INFIT_REVERSE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/reverse.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace infit {
		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> reverse_impl(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::reverse(cont),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// reverse
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> reverse(
			Container const& cont
			)
		{
			return sprout::infit::detail::reverse_impl(cont, sprout::fixed_begin_offset(cont));
		}
	}	// namespace infit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INFIT_REVERSE_HPP
