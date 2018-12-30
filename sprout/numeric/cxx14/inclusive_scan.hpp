/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_CXX14_INCLUSIVE_SCAN_HPP
#define SPROUT_NUMERIC_CXX14_INCLUSIVE_SCAN_HPP

#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/numeric/cxx14/partial_sum.hpp>

namespace sprout {
	//
	// 29.8.8 Inclusive scan
	//
	template<
		typename InputIterator, typename OutputIterator, typename BinaryOperation, typename T,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	inclusive_scan(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op, T init) {
		typedef typename std::iterator_traits<InputIterator>::value_type value_type;
		value_type sum = sprout::move(init);
		*result = sum;
		if (first == last) {
			return ++result;
		}
		sum = binary_op(sum, *first);
		*++result = sum;
		while (++first != last) {
			sum = binary_op(sum, *first);
			*++result = sum;
		}
		return ++result;
	}
	template<
		typename InputIterator, typename OutputIterator, typename BinaryOperation,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	inclusive_scan(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op) {
		return sprout::partial_sum(first, last, result, binary_op);
	}
	template<
		typename InputIterator, typename OutputIterator,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	inclusive_scan(InputIterator first, InputIterator last, OutputIterator result) {
		return sprout::partial_sum(first, last, result);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_CXX14_INCLUSIVE_SCAN_HPP
