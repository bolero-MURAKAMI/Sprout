#ifndef SPROUT_ALGORITHM_FIT_REVERSE_COPY_HPP
#define SPROUT_ALGORITHM_FIT_REVERSE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/reverse_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename BidirectionalIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type reverse_copy_impl(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::reverse_copy(first, last, result)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// reverse_copy
		//
		template<typename BidirectionalIterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type reverse_copy(
			BidirectionalIterator first,
			BidirectionalIterator last,
			Result const& result
			)
		{
			return sprout::fit::detail::reverse_copy_impl(first, last, result, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REVERSE_COPY_HPP
