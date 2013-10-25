/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_ROTATE_HPP
#define SPROUT_ALGORITHM_ROTATE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/algorithm/iter_swap.hpp>

namespace sprout {
	//
	// 25.3.11 Rotate
	//
	template<typename ForwardIterator>
	inline SPROUT_CXX14_CONSTEXPR ForwardIterator
	rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last) {
		if (first == middle) {
			return last;
		} else if (middle == last) {
			return first;
		}
		ForwardIterator first2 = middle;
		while (true) {
			sprout::iter_swap(first, first2);
			++first;
			if (++first2 == last) {
				break;
			}
			if (first == middle) {
				middle = first2;
			}
		}
		ForwardIterator result = first;
		if (first != middle) {
			first2 = middle;
			while (true) {
				sprout::iter_swap(first, first2);
				++first;
				if (++first2 == last) {
					if (first == middle) {
						break;
					}
					first2 = middle;
				} else if (first == middle) {
					middle = first2;
				}
			}
		}
		return result;
	}
}	// namespace sprout

#include <sprout/algorithm/fixed/rotate.hpp>
#include <sprout/algorithm/fit/rotate.hpp>

#endif	// #ifndef SPROUT_ALGORITHM_ROTATE_HPP
