#ifndef SPROUT_NUMERIC_ACCUMLATE_HPP
#define SPROUT_NUMERIC_ACCUMLATE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 26.7.2 Accumulate
	template<typename InputIterator, typename T, typename BinaryOperation>
	SPROUT_CONSTEXPR T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
		return first == last ? init
			: sprout::accumulate(sprout::next(first), last, binary_op(init, *first), binary_op)
			;
	}

	template<typename InputIterator, typename T>
	SPROUT_CONSTEXPR T accumulate(InputIterator first, InputIterator last, T init) {
		return sprout::accumulate(first, last, init, NS_SSCRISK_CEL_OR_SPROUT::plus<typename std::iterator_traits<InputIterator>::value_type>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_ACCUMLATE_HPP
