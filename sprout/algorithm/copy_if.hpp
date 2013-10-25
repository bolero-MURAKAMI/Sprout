/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_COPY_IF_HPP
#define SPROUT_ALGORITHM_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// 25.3.1 Copy
	//
	template<
		typename InputIterator, typename OutputIterator, typename Predicate,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred) {
		for (; first != last; ++first) {
			if (pred(*first)) {
				*result++ = *first;
			}
		}
		return result;
	}
}	// namespace sprout

#include <sprout/algorithm/fixed/copy_if.hpp>
#include <sprout/algorithm/fit/copy_if.hpp>

#endif	// #ifndef SPROUT_ALGORITHM_COPY_IF_HPP
