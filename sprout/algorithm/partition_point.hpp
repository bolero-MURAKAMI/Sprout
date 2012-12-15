#ifndef SPROUT_ALGORITHM_PARTITION_POINT_HPP
#define SPROUT_ALGORITHM_PARTITION_POINT_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		template<typename ForwardIterator, typename Predicate>
		inline SPROUT_CONSTEXPR ForwardIterator
		partition_point_impl(ForwardIterator first, ForwardIterator last, Predicate pred, ForwardIterator mid) {
			return mid == last ? mid
				: pred(*mid) ? sprout::detail::partition_point_impl(
					sprout::next(mid), last, pred,
					sprout::next(mid, 1 + NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::next(mid), last) / 2)
					)
				: sprout::detail::partition_point_impl(
					first, mid, pred,
					sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, mid) / 2)
					)
				;
		}
	}	// namespace detail

	// 25.3.13 Partitions
	//
	//	recursion depth:
	//		[first, last) is RandomAccessIterator -> O(log N)
	//		otherwise -> O(N)
	//
	template<typename ForwardIterator, typename Predicate>
	inline SPROUT_CONSTEXPR ForwardIterator
	partition_point(ForwardIterator first, ForwardIterator last, Predicate pred) {
		return sprout::detail::partition_point_impl(
			first, last, pred,
			sprout::next(first, NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_PARTITION_POINT_HPP
