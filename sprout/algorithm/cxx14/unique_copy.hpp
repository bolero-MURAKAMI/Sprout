/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_UNIQUE_COPY_HPP
#define SPROUT_ALGORITHM_CXX14_UNIQUE_COPY_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// 25.3.9 Unique
	//
	template<
		typename InputIterator, typename OutputIterator,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	unique_copy(InputIterator first, InputIterator last, OutputIterator result) {
		if (first == last) {
			return result;
		}
		typename std::iterator_traits<InputIterator>::value_type value = *first++;
		*result++ = value;
		for (; first != last; ++first) {
			if (!(value == *first)) {
				value = *first;
				*result++ = value;
			}
		}
		return result;
	}

	template<
		typename InputIterator, typename OutputIterator, typename BinaryPredicate,
		typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR OutputIterator
	unique_copy(InputIterator first, InputIterator last, OutputIterator result, BinaryPredicate pred) {
		if (first == last) {
			return result;
		}
		typename std::iterator_traits<InputIterator>::value_type value = *first++;
		*result++ = value;
		for (; first != last; ++first) {
			if (!pred(value, *first)) {
				value = *first;
				*result++ = value;
			}
		}
		return result;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_UNIQUE_COPY_HPP
