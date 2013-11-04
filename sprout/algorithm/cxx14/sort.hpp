/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CXX14_ALGORITHM_SORT_HPP
#define SPROUT_CXX14_ALGORITHM_SORT_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// 25.4.1.1 sort
	//
	// !!! TOTO: implementation
	template<typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	sort(RandomAccessIterator first, RandomAccessIterator last);

	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
}	// namespace sprout

#endif	// #ifndef SPROUT_CXX14_ALGORITHM_SORT_HPP
