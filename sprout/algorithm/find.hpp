#ifndef SPROUT_ALGORITHM_FIND_HPP
#define SPROUT_ALGORITHM_FIND_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.5 Find
	template<typename InputIterator, typename T>
	SPROUT_CONSTEXPR InputIterator find(InputIterator first, InputIterator last, T const& value) {
		return first == last || *first == value ? first
			: sprout::find(sprout::next(first), last, value)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIND_HPP
