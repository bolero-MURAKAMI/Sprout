#ifndef SPROUT_ALGORITHM_COUNT_IF_HPP
#define SPROUT_ALGORITHM_COUNT_IF_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.9 Count
	template<typename InputIterator, typename Predicate>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	count_if(InputIterator first, InputIterator last, Predicate pred) {
		return first == last ? 0
			: (pred(*first) != false ? 1 : 0) + sprout::count_if(sprout::next(first), last, pred)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_COUNT_IF_HPP
