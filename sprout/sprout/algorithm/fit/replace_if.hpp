#ifndef SPROUT_ALGORITHM_FIT_REPLACE_IF_HPP
#define SPROUT_ALGORITHM_FIT_REPLACE_IF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/replace_if.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename T, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type replace_if_impl(
				Container const& cont,
				Predicate pred,
				T const& new_value,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::replace_if(cont, pred, new_value)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// replace_if
		//
		template<typename Container, typename T, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type replace_if(
			Container const& cont,
			Predicate pred,
			T const& new_value
			)
		{
			return sprout::fit::detail::replace_if_impl(cont, pred, new_value, sprout::fixed_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REPLACE_IF_HPP
