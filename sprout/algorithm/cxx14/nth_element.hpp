/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CXX14_ALGORITHM_NTH_ELEMENT_HPP
#define SPROUT_CXX14_ALGORITHM_NTH_ELEMENT_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// 25.4.2 Nth element
	//
	// !!! TODO: implementation
	template<typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last);

	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, Compare comp);
}	// namespace sprout

#endif	// #ifndef SPROUT_CXX14_ALGORITHM_NTH_ELEMENT_HPP
