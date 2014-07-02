/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_MERGE_HPP
#define SPROUT_ALGORITHM_CXX14_MERGE_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/copy.hpp>
#include <sprout/functional/less.hpp>

namespace sprout {
	//
	// 25.4.4 Merge
	//
	template<
		typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Compare,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp) {
		while (true) {
			if (first1 == last1) {
				return sprout::copy(first2, last2, result);
			}
			if (first2 == last2) {
				return sprout::copy(first1, last1, result);
			}
			*result++ = comp(*first2, *first1)
				? *first2++
				: *first1++
				;
		}
	}

	template<
		typename InputIterator1, typename InputIterator2, typename OutputIterator,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
		return sprout::merge(
			first1, last1, first2, last2, result,
			sprout::less<>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_MERGE_HPP
