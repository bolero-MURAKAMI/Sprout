/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_CXX14_IOTA_HPP
#define SPROUT_NUMERIC_CXX14_IOTA_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// 26.7.6 Iota
	//
	template<typename ForwardIterator, typename T>
	inline SPROUT_CXX14_CONSTEXPR void
	iota(ForwardIterator first, ForwardIterator last, T value) {
		while (first != last) {
			*first++ = value;
			++value;
		}
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_CXX14_IOTA_HPP
