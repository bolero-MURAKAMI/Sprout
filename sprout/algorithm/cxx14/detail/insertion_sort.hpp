/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_DETAIL_INSERTION_SORT_HPP
#define SPROUT_ALGORITHM_CXX14_DETAIL_INSERTION_SORT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/algorithm/cxx14/move_backward.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR void
		unguarded_linear_insert(RandomAccessIterator last, Compare comp) {
			typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
			value_type val = sprout::move(*last);
			RandomAccessIterator next = last;
			--next;
			while (comp(val, *next)) {
				*last = sprout::move(*next);
				last = next;
				--next;
			}
			*last = sprout::move(val);
		}

		template<typename RandomAccessIterator, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR void
		insertion_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
			if (first == last) {
				return;
			}
			for (RandomAccessIterator i = first + 1; i != last; ++i) {
				if (comp(*i, *first)) {
					value_type val = sprout::move(*i);
					sprout::move_backward(first, i, i + 1);
					*first = sprout::move(val);
				} else {
					sprout::detail::unguarded_linear_insert(i, comp);
				}
			}
		}
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_DETAIL_INSERTION_SORT_HPP
