/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_INPLACE_MERGE_HPP
#define SPROUT_ALGORITHM_CXX14_INPLACE_MERGE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// 25.4.4 Merge
	//
	// !!! TODO: implementation
	template<typename BidirectionalIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	inplace_merge(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last);

	template<typename BidirectionalIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	inplace_merge(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Compare comp);
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_INPLACE_MERGE_HPP
