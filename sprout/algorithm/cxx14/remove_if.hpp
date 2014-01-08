/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CXX14_ALGORITHM_REMOVE_IF_HPP
#define SPROUT_CXX14_ALGORITHM_REMOVE_IF_HPP

#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	//
	// 25.3.8 Remove
	//
	template<typename ForwardIterator, typename Predicate>
	inline SPROUT_CXX14_CONSTEXPR ForwardIterator
	remove_if(ForwardIterator first, ForwardIterator last, Predicate pred) {
		ForwardIterator result = first;
		for (; first != last; ++first) {
			if (!pred(*first)) {
				*result++ = sprout::move(*first);
			}
		}
		return result;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CXX14_ALGORITHM_REMOVE_IF_HPP
