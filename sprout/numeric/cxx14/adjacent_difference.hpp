/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_CXX14_ADJACENT_DIFFERENCE_HPP
#define SPROUT_NUMERIC_CXX14_ADJACENT_DIFFERENCE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// 26.7.5 Adjacent difference
	//
	template<
		typename InputIterator, typename OutputIterator, typename BinaryOperation,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op) {
		typedef typename std::iterator_traits<InputIterator>::value_type value_type;
		if (first == last) {
			return result;
		}
		value_type acc = *first;
		*result = acc;
		while (++first != last) {
			value_type val = *first;
			*++result = binary_op(val, acc);
			acc = sprout::move(val);
		}
		return ++result;
	}
	template<
		typename InputIterator, typename OutputIterator,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	adjacent_difference(InputIterator first, InputIterator last, OutputIterator result) {
		return sprout::adjacent_difference(
			first, last, result,
			NS_SSCRISK_CEL_OR_SPROUT::minus<typename std::iterator_traits<InputIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_CXX14_ADJACENT_DIFFERENCE_HPP
