/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CXX14_ALGORITHM_GENERATE_N_HPP
#define SPROUT_CXX14_ALGORITHM_GENERATE_N_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// 25.3.7 Generate
	//
	template<
		typename OutputIterator, typename Size, typename Generator,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	generate_n(OutputIterator first, Size n, Generator gen) {
		 while (n-- > 0) {
			*first++ = gen();
		}
		return first;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CXX14_ALGORITHM_GENERATE_N_HPP
