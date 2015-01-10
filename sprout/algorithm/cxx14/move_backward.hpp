/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_MOVE_BACKWARD_HPP
#define SPROUT_ALGORITHM_CXX14_MOVE_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	//
	// 25.3.2 Move
	//
	template<
		typename BidirectionalIterator1, typename BidirectionalIterator2,
		typename sprout::enabler_if<sprout::is_iterator_outputable<BidirectionalIterator2>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR BidirectionalIterator2
	move_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result) {
		while (first != last) {
			*--result = sprout::move(*--first);
		}
		return result;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_MOVE_BACKWARD_HPP
