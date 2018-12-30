/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_FILL_N_HPP
#define SPROUT_ALGORITHM_CXX14_FILL_N_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// 25.3.6 Fill
	//
	template<
		typename OutputIterator, typename Size, typename T,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	fill_n(OutputIterator first, Size n, T const& value) {
		while (n-- > 0) {
			*first++ = value;
		}
		return first;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_FILL_N_HPP
