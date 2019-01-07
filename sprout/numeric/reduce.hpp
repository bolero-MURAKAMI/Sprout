/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_REDUCE_HPP
#define SPROUT_NUMERIC_REDUCE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/accumulate.hpp>

namespace sprout {
	//
	// reduce
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::value_type
	reduce(InputIterator first, InputIterator last) {
		return sprout::accumulate(first, last, typename std::iterator_traits<InputIterator>::value_type());
	}

	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR T
	reduce(InputIterator first, InputIterator last, T init) {
		return sprout::accumulate(first, last, init);
	}

	template<typename InputIterator, typename T, typename BinaryOperation>
	inline SPROUT_CONSTEXPR T
	reduce(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
		return sprout::accumulate(first, last, init, binary_op);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_REDUCE_HPP
