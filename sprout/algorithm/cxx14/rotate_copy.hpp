/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_ROTATE_COPY_HPP
#define SPROUT_ALGORITHM_CXX14_ROTATE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/copy.hpp>

namespace sprout {
	//
	// 25.3.11 Rotate
	//
	template<
		typename ForwardIterator, typename OutputIterator,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator result) {
		return sprout::copy(first, middle, sprout::copy(middle, last, result));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_ROTATE_COPY_HPP
