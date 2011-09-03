#ifndef SPROUT_ALGORITHM_FIT_PARTITION_HPP
#define SPROUT_ALGORITHM_FIT_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/partition.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type partition_impl(
				Container const& cont,
				Predicate pred,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::partition(cont, pred)),
					offset,
					offset + sprout::size(cont) - NS_SSCRISK_CEL_OR_SPROUT_DETAIL::count_if(sprout::begin(cont), sprout::end(cont), pred)
					);
			}
		}	// namespace detail
		//
		// partition
		//
		template<typename Container, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type partition(
			Container const& cont,
			Predicate pred
			)
		{
			return sprout::fit::detail::partition_impl(cont, pred, sprout::fixed_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_PARTITION_HPP
