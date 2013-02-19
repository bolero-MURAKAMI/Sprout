#ifndef SPROUT_ALGORITHM_FIT_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIT_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/partition_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/detail/algorithm/count_n_if.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT
#include <sprout/iterator/type_traits/is_iterator.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			partition_copy_impl(
				InputIterator first, InputIterator last, Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::partition_copy(first, last, result, pred)),
					offset,
					offset + sprout::detail::count_n_if(
						first,
						NS_SSCRISK_CEL_OR_SPROUT::min(
							sprout::distance(first, last), sprout::size(result)
							),
						pred
						)
					);
			}
		}	// namespace detail
		//
		// partition_copy
		//
		template<typename InputIterator, typename Result, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		partition_copy(InputIterator first, InputIterator last, Result const& result, Predicate pred) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::partition_copy_impl(first, last, result, pred, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_PARTITION_COPY_HPP
