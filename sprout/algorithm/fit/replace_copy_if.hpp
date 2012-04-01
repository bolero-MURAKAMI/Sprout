#ifndef SPROUT_ALGORITHM_FIT_REPLACE_COPY_IF_HPP
#define SPROUT_ALGORITHM_FIT_REPLACE_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/replace_copy_if.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename T, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type replace_copy_if_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				Predicate pred,
				T const& new_value,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::replace_copy_if(first, last, result, pred, new_value)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// replace_copy_if
		//
		template<typename InputIterator, typename Result, typename T, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type replace_copy_if(
			InputIterator first,
			InputIterator last,
			Result const& result,
			Predicate pred,
			T const& new_value
			)
		{
			return sprout::fit::detail::replace_copy_if_impl(first, last, result, pred, new_value, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REPLACE_COPY_IF_HPP
