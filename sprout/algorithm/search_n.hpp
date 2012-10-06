#ifndef SPROUT_ALGORITHM_SEARCH_N_HPP
#define SPROUT_ALGORITHM_SEARCH_N_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.13 Search
	template<typename ForwardIterator, typename Size, typename T>
	inline SPROUT_CONSTEXPR ForwardIterator
	search_n(ForwardIterator first, ForwardIterator last, Size count, T const& value) {
		return first == last || count == 0 ? first
			: sprout::next(first) == last && count > 1 ? last
			: *first == value
				&& sprout::search_n(sprout::next(first), last, count - 1, value) == sprout::next(first)
				? first
			: sprout::search_n(sprout::next(first), last, count, value)
			;
	}

	template<typename ForwardIterator, typename Size, typename T, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator
	search_n(ForwardIterator first, ForwardIterator last, Size count, T const& value, BinaryPredicate pred) {
		return first == last || count == 0 ? first
			: sprout::next(first) == last && count > 1 ? last
			: *first == value
				&& sprout::search_n(sprout::next(first), last, count - 1, value, pred) == sprout::next(first)
				? first
			: sprout::search_n(sprout::next(first), last, count, value, pred)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_SEARCH_N_HPP
