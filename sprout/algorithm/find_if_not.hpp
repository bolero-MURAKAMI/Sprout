#ifndef SPROUT_ALGORITHM_FIND_IF_NOT_HPP
#define SPROUT_ALGORITHM_FIND_IF_NOT_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.5 Find
	template<typename InputIterator, typename Predicate>
	inline SPROUT_CONSTEXPR InputIterator
	find_if_not(InputIterator first, InputIterator last, Predicate pred) {
		return first == last || !pred(*first) ? first
			: sprout::find_if_not(sprout::next(first), last, pred)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_IF_NOT_HPP
