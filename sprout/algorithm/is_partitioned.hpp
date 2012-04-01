#ifndef SPROUT_ALGORITHM_IS_PARTITIONED_HPP
#define SPROUT_ALGORITHM_IS_PARTITIONED_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		template<typename InputIterator, typename Predicate>
		SPROUT_CONSTEXPR bool is_partitioned_impl(InputIterator first, InputIterator last, Predicate pred, bool cond = true) {
			return first == last ? true
				: cond ? sprout::detail::is_partitioned_impl(sprout::next(first), last, pred, pred(*first))
				: pred(*first) ? false
				: sprout::detail::is_partitioned_impl(sprout::next(first), last, pred, false)
				;
		}
	}	// namespace detail

	// 25.3.13 Partitions
	template<typename InputIterator, typename Predicate>
	SPROUT_CONSTEXPR bool is_partitioned(InputIterator first, InputIterator last, Predicate pred) {
		return sprout::detail::is_partitioned_impl(first, last, pred);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_PARTITIONED_HPP
