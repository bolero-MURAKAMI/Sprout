#ifndef SPROUT_ALGORITHM_FIT_REPLACE_COPY_HPP
#define SPROUT_ALGORITHM_FIT_REPLACE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/replace_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename T>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type replace_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				T const& old_value,
				T const& new_value,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::replace_copy(first, last, result, old_value, new_value)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// replace_copy
		//
		template<typename InputIterator, typename Result, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type replace_copy(
			InputIterator first,
			InputIterator last,
			Result const& result,
			T const& old_value,
			T const& new_value
			)
		{
			return sprout::fit::detail::replace_copy_impl(first, last, result, old_value, new_value, sprout::fixed_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REPLACE_COPY_HPP
