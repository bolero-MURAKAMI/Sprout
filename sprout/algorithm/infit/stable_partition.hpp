#ifndef SPROUT_ALGORITHM_INFIT_STABLE_PARTITION_HPP
#define SPROUT_ALGORITHM_INFIT_STABLE_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/stable_partition.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace infit {
		namespace detail {
			template<typename Container, typename Predicate>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> stable_partition_impl(
				Container const& cont,
				Predicate pred,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::stable_partition(cont, pred),
					offset,
					offset + sprout::size(cont) - NS_SSCRISK_CEL_OR_SPROUT_DETAIL::count_if(sprout::begin(cont), sprout::end(cont), pred)
					);
			}
		}	// namespace detail
		//
		// stable_partition
		//
		template<typename Container, typename Predicate>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> stable_partition(
			Container const& cont,
			Predicate pred
			)
		{
			return sprout::infit::detail::stable_partition_impl(cont, pred, sprout::fixed_begin_offset(cont));
		}
	}	// namespace infit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_INFIT_STABLE_PARTITION_HPP
