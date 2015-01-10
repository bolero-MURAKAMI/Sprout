/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_REMOVE_HPP
#define SPROUT_ALGORITHM_CXX14_REMOVE_HPP

#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	//
	// 25.3.8 Remove
	//
	template<typename ForwardIterator, typename T>
	inline SPROUT_CXX14_CONSTEXPR ForwardIterator
	remove(ForwardIterator first, ForwardIterator last, T const& value) {
		ForwardIterator result = first;
		for (; first != last; ++first) {
			if (!(*first == value)) {
				*result++ = sprout::move(*first);
			}
		}
		return result;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_REMOVE_HPP
