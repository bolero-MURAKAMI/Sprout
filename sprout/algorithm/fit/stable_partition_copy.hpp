#ifndef SPROUT_ALGORITHM_FIT_STABLE_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIT_STABLE_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/stable_partition_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Iterator, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type stable_partition_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::stable_partition_copy(first, last, result, pred)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::count_if(first, last, pred), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// stable_partition_copy
		//
		template<typename Iterator, typename Result, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type stable_partition_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			Predicate pred
			)
		{
			return sprout::fit::detail::stable_partition_copy_impl(first, last, result, pred, sprout::fixed_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_STABLE_PARTITION_COPY_HPP
