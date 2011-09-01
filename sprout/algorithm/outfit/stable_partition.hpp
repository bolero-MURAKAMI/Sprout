#ifndef SPROUT_ALGORITHM_OUTFIT_STABLE_PARTITION_HPP
#define SPROUT_ALGORITHM_OUTFIT_STABLE_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/stable_partition.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
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
					offset + sprout::size(cont)
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
			return sprout::outfit::detail::stable_partition_impl(cont, pred, sprout::fixed_begin_offset(cont));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_STABLE_PARTITION_HPP
