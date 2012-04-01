#ifndef SPROUT_ALGORITHM_FIT_COPY_BACKWARD_HPP
#define SPROUT_ALGORITHM_FIT_COPY_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/copy_backward.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename BidirectionalIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type copy_backward_impl(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::copy_backward(first, last, result)),
					offset - NS_SSCRISK_CEL_OR_SPROUT::min(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last), sprout::size(result)),
					offset
					);
			}
		}	// namespace detail
		//
		// copy_backward
		//
		template<typename BidirectionalIterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type copy_backward(
			BidirectionalIterator first,
			BidirectionalIterator last,
			Result const& result
			)
		{
			return sprout::fit::detail::copy_backward_impl(first, last, result, sprout::internal_end_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_COPY_BACKWARD_HPP
