/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_DETAIL_HEAP_TOOL_HPP
#define SPROUT_ALGORITHM_CXX14_DETAIL_HEAP_TOOL_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	namespace detail {
		template<typename Compare, typename RandomAccessIterator>
		inline SPROUT_CXX14_CONSTEXPR void
		push_heap_front(
			RandomAccessIterator first, RandomAccessIterator, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type len
			)
		{
			typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
			typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
			if (len > 1) {
				difference_type p = 0;
				RandomAccessIterator pp = first;
				difference_type c = 2;
				RandomAccessIterator cp = first + c;
				if (c == len || comp(*cp, *(cp - 1))) {
					--c;
					--cp;
				}
				if (comp(*pp, *cp)) {
					value_type t(sprout::move(*pp));
					do {
						*pp = sprout::move(*cp);
						pp = cp;
						p = c;
						c = (p + 1) * 2;
						if (c > len) {
							break;
						}
						cp = first + c;
						if (c == len || comp(*cp, *(cp - 1))) {
							--c;
							--cp;
						}
					} while (comp(t, *cp));
					*pp = sprout::move(t);
				}
			}
		}
		template<typename Compare, typename RandomAccessIterator>
		inline SPROUT_CXX14_CONSTEXPR void
		push_heap_back(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp,
			typename std::iterator_traits<RandomAccessIterator>::difference_type len
			)
		{
			typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
			if (len > 1) {
				len = (len - 2) / 2;
				RandomAccessIterator ptr = first + len;
				if (comp(*ptr, *--last)) {
					value_type t(sprout::move(*last));
					do {
						*last = sprout::move(*ptr);
						last = ptr;
						if (len == 0) {
							break;
						}
						len = (len - 1) / 2;
						ptr = first + len;
					} while (comp(*ptr, t));
					*last = sprout::move(t);
				}
			}
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_DETAIL_HEAP_TOOL_HPP
