#ifndef SPROUT_ALGORITHM_ANY_OF_HPP
#define SPROUT_ALGORITHM_ANY_OF_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.2 Any of
	template<typename InputIterator, typename Predicate>
	inline SPROUT_CONSTEXPR bool any_of(InputIterator first, InputIterator last, Predicate pred) {
		return first == last ? false
			: pred(*first) == true || sprout::any_of(sprout::next(first), last, pred)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_ANY_OF_HPP
