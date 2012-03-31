#ifndef SPROUT_ALGORITHM_FIT_ROTATE_HPP
#define SPROUT_ALGORITHM_FIT_ROTATE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/rotate.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type rotate_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::const_iterator middle,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::rotate(cont, middle)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// rotate
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type rotate(
			Container const& cont,
			typename sprout::container_traits<Container>::const_iterator middle
			)
		{
			return sprout::fit::detail::rotate_impl(cont, middle, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_ROTATE_HPP
