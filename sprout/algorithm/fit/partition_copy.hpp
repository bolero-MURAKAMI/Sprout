#ifndef SPROUT_ALGORITHM_FIT_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIT_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/partition_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/detail/algorithm_ext.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type partition_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::partition_copy(first, last, result, pred)),
					offset,
					offset + sprout::detail::count_n_if(
						first,
						NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(
							NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last),
							sprout::size(result)
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
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type partition_copy(
			InputIterator first,
			InputIterator last,
			Result const& result,
			Predicate pred
			)
		{
			return sprout::fit::detail::partition_copy_impl(first, last, result, pred, sprout::fixed_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_PARTITION_COPY_HPP
