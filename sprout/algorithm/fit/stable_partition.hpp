#ifndef SPROUT_ALGORITHM_FIT_STABLE_PARTITION_HPP
#define SPROUT_ALGORITHM_FIT_STABLE_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/stable_partition.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type stable_partition_impl(
				Container const& cont,
				Predicate pred,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::stable_partition(cont, pred)),
					offset,
					offset + sprout::size(cont) - NS_SSCRISK_CEL_OR_SPROUT::count_if(sprout::begin(cont), sprout::end(cont), pred)
					);
			}
		}	// namespace detail
		//
		// stable_partition
		//
		template<typename Container, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type stable_partition(
			Container const& cont,
			Predicate pred
			)
		{
			return sprout::fit::detail::stable_partition_impl(cont, pred, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_STABLE_PARTITION_HPP
