#ifndef SPROUT_ALGORITHM_IS_PARTITIONED_HPP
#define SPROUT_ALGORITHM_IS_PARTITIONED_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/none_of.hpp>
#include <sprout/algorithm/find_if_not.hpp>

namespace sprout {
	// 25.3.13 Partitions
	//
	//	recursion depth:
	//		[first, last) is RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename InputIterator, typename Predicate>
	inline SPROUT_CONSTEXPR bool
	is_partitioned(InputIterator first, InputIterator last, Predicate pred) {
		return sprout::none_of(sprout::find_if_not(first, last, pred), last, pred);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_PARTITIONED_HPP
