/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CXX14_ALGORITHM_PARTIAL_SORT_COPY_HPP
#define SPROUT_CXX14_ALGORITHM_PARTIAL_SORT_COPY_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// 25.4.1.4 partial_sort_copy
	//
	// !!! TODO: implementation
	template<typename InputIterator, typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR RandomAccessIterator
	partial_sort_copy(InputIterator first, InputIterator last, RandomAccessIterator result_first, RandomAccessIterator result_last);

	template<typename InputIterator, typename RandomAccessIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR RandomAccessIterator
	partial_sort_copy(InputIterator first, InputIterator last, RandomAccessIterator result_first, RandomAccessIterator result_last, Compare comp);
}	// namespace sprout

#endif	// #ifndef SPROUT_CXX14_ALGORITHM_PARTIAL_SORT_COPY_HPP
