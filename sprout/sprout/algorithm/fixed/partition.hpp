#ifndef SPROUT_ALGORITHM_FIXED_PARTITION_HPP
#define SPROUT_ALGORITHM_FIXED_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/partition_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// partition
		//
		template<typename Container, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type partition(
			Container const& cont,
			Predicate pred
			)
		{
			return sprout::fixed::partition_copy(sprout::begin(cont), sprout::end(cont), cont, pred);
		}
	}	// namespace fixed

	using sprout::fixed::partition;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_PARTITION_HPP
