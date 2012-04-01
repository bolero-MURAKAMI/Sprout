#ifndef SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP
#define SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/swap_element_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type swap_element_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				InputIterator pos1,
				InputIterator pos2,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::swap_element_copy(first, last, result, pos1, pos2)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// swap_element_copy
		//
		template<typename InputIterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type swap_element_copy(
			InputIterator first,
			InputIterator last,
			Result const& result,
			InputIterator pos1,
			InputIterator pos2
			)
		{
			return sprout::fit::detail::swap_element_copy_impl(first, last, result, pos1, pos2, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP
