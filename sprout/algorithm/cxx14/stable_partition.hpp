/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_STABLE_PARTITION_HPP
#define SPROUT_ALGORITHM_CXX14_STABLE_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/advance.hpp>
#include <sprout/algorithm/find_if_not.hpp>
#include <sprout/algorithm/cxx14/rotate.hpp>

namespace sprout {
	namespace detail {
		template<typename BidirectionalIterator, typename Predicate, typename Distance>
		inline SPROUT_CXX14_CONSTEXPR BidirectionalIterator
		inplace_stable_partition(BidirectionalIterator first, Predicate pred, Distance len) {
			if (len == 1) {
				return first;
			}
			BidirectionalIterator middle = first;
			sprout::advance(middle, len / 2);
			BidirectionalIterator left_split = sprout::detail::inplace_stable_partition(first, pred, len / 2);
			Distance right_len = len - len / 2;
			BidirectionalIterator right_split = sprout::find_if_not(middle, sprout::next(middle, right_len), pred);
			if (right_len) {
				right_split = sprout::detail::inplace_stable_partition(middle, pred, right_len);
			}
			sprout::rotate(left_split, middle, right_split);
			sprout::advance(left_split, sprout::distance(middle, right_split));
			return left_split;
		}
	}	// namespace sprout
	//
	// 25.3.13 Partitions
	//
	template<typename BidirectionalIterator, typename Predicate>
	inline SPROUT_CXX14_CONSTEXPR BidirectionalIterator
	stable_partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred) {
		first = sprout::find_if_not(first, last, pred);
		return first == last ? first
			: sprout::detail::inplace_stable_partition(first, pred, sprout::distance(first, last))
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_STABLE_PARTITION_HPP
