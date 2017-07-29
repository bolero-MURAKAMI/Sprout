/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_COPY_UNTIL_HPP
#define SPROUT_ALGORITHM_CXX14_COPY_UNTIL_HPP

#include <sprout/config.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// copy_until
	//
	template<
		typename InputIterator, typename OutputIterator, typename Predicate,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR sprout::pair<InputIterator, OutputIterator>
	copy_until(InputIterator first, InputIterator last, OutputIterator result, Predicate pred) {
		for (; first != last && !pred(*first); ++first) {
			*result++ = *first;
		}
		return std::make_pair(first, result);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_COPY_UNTIL_HPP
