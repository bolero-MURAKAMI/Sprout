/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_CXX14_TRANSFORM_EXCLUSIVE_SCAN_HPP
#define SPROUT_NUMERIC_CXX14_TRANSFORM_EXCLUSIVE_SCAN_HPP

#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// 29.8.9 Transform exclusive scan
	//
	template<
		typename InputIterator, typename OutputIterator, typename T, typename BinaryOperation, typename UnaryOperation,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	transform_exclusive_scan(InputIterator first, InputIterator last, OutputIterator result, T init, BinaryOperation binary_op, UnaryOperation unary_op) {
		typedef typename std::iterator_traits<InputIterator>::value_type value_type;
		value_type sum = sprout::move(init);
		*result = sum;
		if (first == last) {
			return ++result;
		}
		value_type temp = unary_op(*first);
		while (++first != last) {
			sum = binary_op(sum, temp);
			*++result = sum;
			temp = unary_op(*first);
		}
		return ++result;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_CXX14_TRANSFORM_EXCLUSIVE_SCAN_HPP
