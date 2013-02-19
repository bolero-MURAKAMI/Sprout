#ifndef SPROUT_ALGORITHM_FIT_ROTATE_COPY_HPP
#define SPROUT_ALGORITHM_FIT_ROTATE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/rotate_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename ForwardIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			rotate_copy_impl(
				ForwardIterator first, ForwardIterator middle, ForwardIterator last, Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::rotate_copy(first, middle, last, result)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// rotate_copy
		//
		template<typename ForwardIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Result const& result) {
			return sprout::fit::detail::rotate_copy_impl(first, middle, last, result, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_ROTATE_COPY_HPP
