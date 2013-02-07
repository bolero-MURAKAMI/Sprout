#ifndef SPROUT_ALGORITHM_FIT_FILL_HPP
#define SPROUT_ALGORITHM_FIT_FILL_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/fill.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			fill_impl(
				Container const& cont, T const& value,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::fill(cont, value)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// fill
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		fill(Container const& cont, T const& value) {
			return sprout::fit::detail::fill_impl(cont, value, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_FILL_HPP
