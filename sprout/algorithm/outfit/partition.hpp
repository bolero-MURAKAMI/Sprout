#ifndef SPROUT_ALGORITHM_OUTFIT_PARTITION_HPP
#define SPROUT_ALGORITHM_OUTFIT_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/partition.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace outfit {
		namespace detail {
			template<typename Container, typename Predicate>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> partition_impl(
				Container const& cont,
				Predicate pred,
				typename sprout::fixed_container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::fixed::partition(cont, pred),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// partition
		//
		template<typename Container, typename Predicate>
		SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Container>::fixed_container_type> partition(
			Container const& cont,
			Predicate pred
			)
		{
			return sprout::outfit::detail::partition_impl(cont, pred, sprout::fixed_begin_offset(cont));
		}
	}	// namespace outfit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_OUTFIT_PARTITION_HPP
