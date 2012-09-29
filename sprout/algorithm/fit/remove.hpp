#ifndef SPROUT_ALGORITHM_FIT_REMOVE_HPP
#define SPROUT_ALGORITHM_FIT_REMOVE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/remove.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			remove_impl(
				Container const& cont, T const& value,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::remove(cont, value)),
					offset,
					offset + sprout::size(cont) - NS_SSCRISK_CEL_OR_SPROUT::count(sprout::begin(cont), sprout::end(cont), value)
					);
			}
		}	// namespace detail
		//
		// remove
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		remove(Container const& cont, T const& value) {
			return sprout::fit::detail::remove_impl(cont, value, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REMOVE_HPP
