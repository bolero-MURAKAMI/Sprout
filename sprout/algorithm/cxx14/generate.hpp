/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_GENERATE_HPP
#define SPROUT_ALGORITHM_CXX14_GENERATE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// 25.3.7 Generate
	//
	template<typename ForwardIterator, typename Generator>
	inline SPROUT_CXX14_CONSTEXPR void
	generate(ForwardIterator first, ForwardIterator last, Generator gen) {
		while (first != last) {
			*first++ = gen();
		}
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_GENERATE_HPP
