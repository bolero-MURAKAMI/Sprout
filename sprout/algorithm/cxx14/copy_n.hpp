/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_COPY_N_HPP
#define SPROUT_ALGORITHM_CXX14_COPY_N_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// 25.3.1 Copy
	//
	template<
		typename InputIterator, typename Size, typename OutputIterator,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	copy_n(InputIterator first, Size n, OutputIterator result) {
		for (Size i = 0; i < n; ++i) {
			*result++ = *first++;
		}
		return result;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_COPY_N_HPP
