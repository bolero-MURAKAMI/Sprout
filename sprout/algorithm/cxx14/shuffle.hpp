/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CXX14_ALGORITHM_SHUFFLE_HPP
#define SPROUT_CXX14_ALGORITHM_SHUFFLE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// 25.3.12 Random shuffle
	//
	template<typename RandomAccessIterator, typename UniformRandomNumberGenerator>
	inline SPROUT_CXX14_CONSTEXPR void
	shuffle(RandomAccessIterator first, RandomAccessIterator last, UniformRandomNumberGenerator&& g); // !!!
}	// namespace sprout

#endif	// #ifndef SPROUT_CXX14_ALGORITHM_SHUFFLE_HPP
