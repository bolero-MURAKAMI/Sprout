/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FILL_HPP
#define SPROUT_ALGORITHM_FILL_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// 25.3.6 Fill
	//
	template<typename ForwardIterator, typename T>
	inline SPROUT_CXX14_CONSTEXPR void
	fill(ForwardIterator first, ForwardIterator last, T const& value) {
		while (first != last) {
			*first++ = value;
		}
	}
}	// namespace sprout

#include <sprout/algorithm/fixed/fill.hpp>
#include <sprout/algorithm/fit/fill.hpp>

#endif	// #ifndef SPROUT_ALGORITHM_FILL_HPP
