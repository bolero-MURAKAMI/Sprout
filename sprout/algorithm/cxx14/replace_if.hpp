/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CXX14_ALGORITHM_REPLACE_IF_HPP
#define SPROUT_CXX14_ALGORITHM_REPLACE_IF_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// 25.3.5 Replace
	//
	template<typename ForwardIterator, typename Predicate, typename T>
	inline SPROUT_CXX14_CONSTEXPR void
	replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, T const& new_value) {
		for (; first != last; ++first) {
			if (pred(*first)) {
				*first = new_value;
			}
		}
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CXX14_ALGORITHM_REPLACE_IF_HPP
