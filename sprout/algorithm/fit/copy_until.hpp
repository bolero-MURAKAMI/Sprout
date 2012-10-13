#ifndef SPROUT_ALGORITHM_FIT_COPY_UNTIL_HPP
#define SPROUT_ALGORITHM_FIT_COPY_UNTIL_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/copy_until.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			copy_until_impl(
				InputIterator first, InputIterator last, Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::copy_until(first, last, result, pred)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(
						NS_SSCRISK_CEL_OR_SPROUT::distance(first, NS_SSCRISK_CEL_OR_SPROUT::find_if(first, last, pred)),
						sprout::size(result)
						)
					);
			}
		}	// namespace detail
		//
		// copy_until
		//
		template<typename InputIterator, typename Result, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		copy_until(InputIterator first, InputIterator last, Result const& result, Predicate pred) {
			return sprout::fit::detail::copy_until_impl(first, last, result, pred, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_COPY_UNTIL_HPP
