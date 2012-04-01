#ifndef SPROUT_ALGORITHM_COUNT_HPP
#define SPROUT_ALGORITHM_COUNT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.9 Count
	template<typename InputIterator, typename T>
	SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	count(InputIterator first, InputIterator last, T const& value) {
		return first == last ? 0
			: (*first == value ? 1 : 0) + sprout::count(sprout::next(first), last, value)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_COUNT_HPP
