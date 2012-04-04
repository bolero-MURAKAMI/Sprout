#ifndef SPROUT_ALGORITHM_FIT_REPLACE_HPP
#define SPROUT_ALGORITHM_FIT_REPLACE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/replace.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type replace_impl(
				Container const& cont,
				T const& old_value,
				T const& new_value,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::replace(cont, old_value, new_value)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// replace
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type replace(
			Container const& cont,
			T const& old_value,
			T const& new_value
			)
		{
			return sprout::fit::detail::replace_impl(cont, old_value, new_value, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REPLACE_HPP
