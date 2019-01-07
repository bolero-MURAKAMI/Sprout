/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_NTH_ELEMENT_HPP
#define SPROUT_ALGORITHM_CXX14_NTH_ELEMENT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/algorithm/cxx14/detail/sort_tool.hpp>
#include <sprout/utility/swap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename Compare, typename RandomAccessIterator>
		inline SPROUT_CXX14_CONSTEXPR void
		nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, Compare comp) {
			typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
			difference_type const limit = 7;
			while (true) {
				if (nth == last) {
					return;
				}
				difference_type len = last - first;
				switch (len) {
				case 0:
				case 1:
					return;
				case 2:
					if (comp(*--last, *first)) {
						sprout::swap(*first, *last);
					}
					return;
				case 3:
					{
						RandomAccessIterator m = first;
						sprout::detail::sort3<Compare>(first, ++m, --last, comp);
					}
					return;
				}
				if (len <= limit) {
					sprout::detail::selection_sort<Compare>(first, last, comp);
					return;
				}
				RandomAccessIterator m = first + len / 2;
				RandomAccessIterator lm1 = last;
				unsigned n_swaps = sprout::detail::sort3<Compare>(first, m, --lm1, comp);
				RandomAccessIterator i = first;
				RandomAccessIterator j = lm1;
				if (!comp(*i, *m)) {
					bool restart_flag = false;
					while (true) {
						if (i == --j) {
							++i;
							j = last;
							if (!comp(*first, *--j)) {
								while (true) {
									if (i == j) {
										return;
									}
									if (comp(*first, *i)) {
										sprout::swap(*i, *j);
										++n_swaps;
										++i;
										break;
									}
									++i;
								}
							}
							if (i == j) {
								return;
							}
							while (true) {
								while (!comp(*first, *i)) {
									++i;
								}
								while (comp(*first, *--j))
									;
								if (i >= j) {
									break;
								}
								sprout::swap(*i, *j);
								++n_swaps;
								++i;
							}
							if (nth < i) {
								return;
							}
							first = i;
							restart_flag = true;
							break;
						}
						if (comp(*j, *m)) {
							sprout::swap(*i, *j);
							++n_swaps;
							break;
						}
					}
					if (restart_flag) {
						continue;
					}
				}
				++i;
				if (i < j) {
					while (true) {
						while (comp(*i, *m)) {
							++i;
						}
						while (!comp(*--j, *m))
							;
						if (i >= j) {
							break;
						}
						sprout::swap(*i, *j);
						++n_swaps;
						if (m == i) {
							m = j;
						}
						++i;
					}
				}
				if (i != m && comp(*m, *i)) {
					sprout::swap(*i, *m);
					++n_swaps;
				}
				if (nth == i) {
					return;
				}
				do {
					bool not_sorted_flag = false;
					if (n_swaps == 0) {
						if (nth < i) {
							j = m = first;
							while (++j != i) {
								if (comp(*j, *m)) {
									not_sorted_flag = true;
									break;
								}
								m = j;
							}
							if (not_sorted_flag) {
								break;
							}
							return;
						} else {
							j = m = i;
							while (++j != last) {
								if (comp(*j, *m)) {
									not_sorted_flag = true;
									break;
								}
								m = j;
							}
							if (not_sorted_flag) {
								break;
							}
							return;
						}
					}
				} while (false);
				if (nth < i) {
					last = i;
				} else {
					first = ++i;
				}
			}
		}
	}	// namespace detail
	//
	// 25.4.2 Nth element
	//
	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, Compare comp) {
		typedef typename std::add_lvalue_reference<Compare>::type compare_ref;
		sprout::detail::nth_element<compare_ref>(first, nth, last, comp);
	}

	template<typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last) {
		sprout::nth_element(
			first, nth, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<RandomAccessIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_NTH_ELEMENT_HPP
