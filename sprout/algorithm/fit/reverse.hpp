#ifndef SPROUT_ALGORITHM_FIT_REVERSE_HPP
#define SPROUT_ALGORITHM_FIT_REVERSE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/reverse.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type reverse_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::reverse(cont)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// reverse
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type reverse(
			Container const& cont
			)
		{
			return sprout::fit::detail::reverse_impl(cont, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REVERSE_HPP
