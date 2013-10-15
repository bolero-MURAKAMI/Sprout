/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_COPY_BACKWARD_HPP
#define SPROUT_ALGORITHM_COPY_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy_backward.hpp>

namespace sprout {
	//
	// 25.3.1 Copy
	//
	template<
		typename BidirectionalIterator1, typename BidirectionalIterator2,
		typename sprout::enabler_if<sprout::is_output_iterator<BidirectionalIterator2>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR BidirectionalIterator2
	copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result) {
		while (first != last) {
			*--result = *--first;
		}
		return result;
	}

	template<
		typename BidirectionalIterator, typename Result,
		typename sprout::enabler_if<!sprout::is_output_iterator<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
	copy_backward(BidirectionalIterator first, BidirectionalIterator last, Result const& result) {
		return sprout::fixed::copy_backward(first, last, result);
	}

	template<typename Result, typename BidirectionalIterator>
	inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
	copy_backward(BidirectionalIterator first, BidirectionalIterator last) {
		return sprout::fixed::copy_backward<Result>(first, last);
	}
}	// namespace sprout

#include <sprout/algorithm/fixed/copy_backward.hpp>
#include <sprout/algorithm/fit/copy_backward.hpp>

#endif	// #ifndef SPROUT_ALGORITHM_COPY_BACKWARD_HPP
