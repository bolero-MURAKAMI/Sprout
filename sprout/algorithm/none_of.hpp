#ifndef SPROUT_ALGORITHM_NONE_OF_HPP
#define SPROUT_ALGORITHM_NONE_OF_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.3 None of
	template <typename InputIterator, typename Predicate>
	inline SPROUT_CONSTEXPR bool none_of(InputIterator first, InputIterator last, Predicate pred) {
		return first == last ? true
			: pred(*first) == false && sprout::none_of(sprout::next(first), last, pred)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_NONE_OF_HPP
