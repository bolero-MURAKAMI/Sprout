#ifndef SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP
#define SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/swap_element_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename ForwardIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			swap_element_copy_impl(
				ForwardIterator first, ForwardIterator last, Result const& result, ForwardIterator pos1, ForwardIterator pos2,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::swap_element_copy(first, last, result, pos1, pos2)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// swap_element_copy
		//
		template<typename ForwardIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		swap_element_copy(ForwardIterator first, ForwardIterator last, Result const& result, ForwardIterator pos1, ForwardIterator pos2) {
			return sprout::fit::detail::swap_element_copy_impl(first, last, result, pos1, pos2, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP
