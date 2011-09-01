#ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_HPP
#define SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/stable_partition_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// stable_partition
		//
		template<typename Container, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Container>::fixed_container_type stable_partition(
			Container const& cont,
			Predicate pred
			)
		{
			return sprout::fixed::stable_partition_copy(sprout::begin(cont), sprout::end(cont), cont, pred);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_HPP
