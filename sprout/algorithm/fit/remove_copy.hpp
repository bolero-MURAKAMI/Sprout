#ifndef SPROUT_ALGORITHM_FIT_REMOVE_COPY_HPP
#define SPROUT_ALGORITHM_FIT_REMOVE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/remove_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Iterator, typename Result, typename T>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type remove_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				T const& value,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::remove_copy(first, last, result, value)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last) - NS_SSCRISK_CEL_OR_SPROUT_DETAIL::count(first, last, value), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// remove_copy
		//
		template<typename Iterator, typename Result, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type remove_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			T const& value
			)
		{
			return sprout::fit::detail::remove_copy_impl(first, last, result, value, sprout::fixed_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REMOVE_COPY_HPP
