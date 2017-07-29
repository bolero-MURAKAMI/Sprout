/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_FOR_EACH_HPP
#define SPROUT_ALGORITHM_CXX14_FOR_EACH_HPP

#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	//
	// 25.2.4 For each
	//
	template<typename InputIterator, typename Function>
	inline SPROUT_CXX14_CONSTEXPR Function
	for_each(InputIterator first, InputIterator last, Function f) {
		for (; first != last; ++first) {
			f(*first);
		}
		return sprout::move(f);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_FOR_EACH_HPP
