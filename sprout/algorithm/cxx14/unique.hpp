/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_UNIQUE_HPP
#define SPROUT_ALGORITHM_CXX14_UNIQUE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	//
	// 25.3.9 Unique
	//
	template<typename ForwardIterator>
	inline SPROUT_CXX14_CONSTEXPR ForwardIterator
	unique(ForwardIterator first, ForwardIterator last) {
		if (first == last) {
			return first;
		}
		ForwardIterator result = first;
		typename std::iterator_traits<ForwardIterator>::value_type value = sprout::move(*first++);
		for (; first != last; ++first) {
			if (!(value == *first)) {
				*result++ = sprout::move(value);
				value = sprout::move(*first);
			}
		}
		*result++ = sprout::move(value);
		return result;
	}
	template<typename ForwardIterator, typename BinaryPredicate>
	inline SPROUT_CXX14_CONSTEXPR ForwardIterator
	unique(ForwardIterator first, ForwardIterator last, BinaryPredicate pred) {
		if (first == last) {
			return first;
		}
		ForwardIterator result = first;
		typename std::iterator_traits<ForwardIterator>::value_type value = sprout::move(*first++);
		for (; first != last; ++first) {
			if (!pred(value, *first)) {
				*result++ = sprout::move(value);
				value = sprout::move(*first);
			}
		}
		*result++ = sprout::move(value);
		return result;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_UNIQUE_HPP
