/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CXX14_ALGORITHM_SORT_HPP
#define SPROUT_CXX14_ALGORITHM_SORT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/algorithm/min_element.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/std_type_traits.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	namespace detail {
		template<typename Compare, typename ForwardIterator>
		inline SPROUT_CXX14_CONSTEXPR unsigned
		sort3(ForwardIterator x, ForwardIterator y, ForwardIterator z, Compare comp) {
			unsigned r = 0;
			if (!comp(*y, *x)) {
				if (!comp(*z, *y))
					return r;
				sprout::swap(*y, *z);
				r = 1;
				if (comp(*y, *x)) {
					sprout::swap(*x, *y);
					r = 2;
				}
				return r;
			}
			if (comp(*z, *y)) {
				sprout::swap(*x, *z);
				r = 1;
				return r;
			}
			sprout::swap(*x, *y);
			r = 1;
			if (comp(*z, *y)) {
				sprout::swap(*y, *z);
				r = 2;
			}
			return r;
		}
		template<typename Compare, typename ForwardIterator>
		inline SPROUT_CXX14_CONSTEXPR unsigned
		sort4(ForwardIterator x1, ForwardIterator x2, ForwardIterator x3, ForwardIterator x4, Compare comp) {
			unsigned r = sprout::detail::sort3<Compare>(x1, x2, x3, comp);
			if (comp(*x4, *x3)) {
				sprout::swap(*x3, *x4);
				++r;
				if (comp(*x3, *x2)) {
					sprout::swap(*x2, *x3);
					++r;
					if (comp(*x2, *x1)) {
						sprout::swap(*x1, *x2);
						++r;
					}
				}
			}
			return r;
		}
		template<typename Compare, typename ForwardIterator>
		inline SPROUT_CXX14_CONSTEXPR unsigned
		sort5(ForwardIterator x1, ForwardIterator x2, ForwardIterator x3, ForwardIterator x4, ForwardIterator x5, Compare comp) {
			unsigned r = sprout::detail::sort4<Compare>(x1, x2, x3, x4, comp);
			if (comp(*x5, *x4)) {
				sprout::swap(*x4, *x5);
				++r;
				if (comp(*x4, *x3)) {
					sprout::swap(*x3, *x4);
					++r;
					if (comp(*x3, *x2)) {
						sprout::swap(*x2, *x3);
						++r;
						if (comp(*x2, *x1)) {
							sprout::swap(*x1, *x2);
							++r;
						}
					}
				}
			}
			return r;
		}
		template<typename Compare, typename BirdirectionalIterator>
		inline SPROUT_CXX14_CONSTEXPR void
		selection_sort(BirdirectionalIterator first, BirdirectionalIterator last, Compare comp) {
			BirdirectionalIterator lm1 = last;
			for (--lm1; first != lm1; ++first) {
				BirdirectionalIterator i = sprout::min_element(first, last, comp);
				if (i != first) {
					sprout::swap(*first, *i);
				}
			}
		}
		template<typename Compare, typename BirdirectionalIterator>
		inline SPROUT_CXX14_CONSTEXPR void
		insertion_sort(BirdirectionalIterator first, BirdirectionalIterator last, Compare comp) {
			typedef typename std::iterator_traits<BirdirectionalIterator>::value_type value_type;
			if (first != last) {
				BirdirectionalIterator i = first;
				for (++i; i != last; ++i) {
					BirdirectionalIterator j = i;
					value_type t(sprout::move(*j));
					for (BirdirectionalIterator k = i; k != first && comp(t, *--k); --j) {
						*j = sprout::move(*k);
					}
					*j = sprout::move(t);
				}
			}
		}
		template<typename Compare, typename RandomAccessIterator>
		inline SPROUT_CXX14_CONSTEXPR void
		insertion_sort_3(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
			RandomAccessIterator j = first + 2;
			sprout::detail::sort3<Compare>(first, first + 1, j, comp);
			for (RandomAccessIterator i = j + 1; i != last; ++i) {
				if (comp(*i, *j)) {
					value_type t(sprout::move(*i));
					RandomAccessIterator k = j;
					j = i;
					do {
						*j = sprout::move(*k);
						j = k;
					} while (j != first && comp(t, *--k));
					*j = sprout::move(t);
				}
				j = i;
			}
		}
		template<typename Compare, typename RandomAccessIterator>
		inline SPROUT_CXX14_CONSTEXPR bool
		insertion_sort_incomplete(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			switch (last - first) {
			case 0:
			case 1:
				return true;
			case 2:
				if (comp(*--last, *first)) {
					sprout::swap(*first, *last);
				}
				return true;
			case 3:
				sprout::detail::sort3<Compare>(first, first + 1, --last, comp);
				return true;
			case 4:
				sprout::detail::sort4<Compare>(first, first + 1, first + 2, --last, comp);
				return true;
			case 5:
				sprout::detail::sort5<Compare>(first, first + 1, first + 2, first + 3, --last, comp);
				return true;
			}
			typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
			RandomAccessIterator j = first+2;
			sprout::detail::sort3<Compare>(first, first + 1, j, comp);
			unsigned const limit = 8;
			unsigned count = 0;
			for (RandomAccessIterator i = j + 1; i != last; ++i) {
				if (comp(*i, *j)) {
					value_type t(sprout::move(*i));
					RandomAccessIterator k = j;
					j = i;
					do {
						*j = sprout::move(*k);
						j = k;
					} while (j != first && comp(t, *--k));
					*j = sprout::move(t);
					if (++count == limit) {
						return ++i == last;
					}
				}
				j = i;
			}
			return true;
		}
		template<typename Compare, typename RandomAccessIterator>
		SPROUT_CXX14_CONSTEXPR void
		sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
		template<typename Compare, typename RandomAccessIterator>
		inline SPROUT_CXX14_CONSTEXPR bool
		sort_impl(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			typedef typename std::decay<RandomAccessIterator>::type iterator;
			typedef typename std::iterator_traits<iterator>::difference_type difference_type;
			typedef typename std::iterator_traits<iterator>::value_type value_type;
			difference_type const limit
				= sprout::is_trivially_copy_constructible<value_type>::value && sprout::is_trivially_copy_assignable<value_type>::value
				? 30
				: 6
				;
			difference_type len = last - first;
			switch (len) {
			case 0:
			case 1:
				return true;
			case 2:
				if (comp(*--last, *first)) {
					sprout::swap(*first, *last);
				}
				return true;
			case 3:
				sprout::detail::sort3<Compare>(first, first + 1, --last, comp);
				return true;
			case 4:
				sprout::detail::sort4<Compare>(first, first + 1, first + 2, --last, comp);
				return true;
			case 5:
				sprout::detail::sort5<Compare>(first, first + 1, first + 2, first + 3, --last, comp);
				return true;
			}
			if (len <= limit) {
				sprout::detail::insertion_sort_3<Compare>(first, last, comp);
				return true;
			}
			iterator m = first;
			iterator lm1 = last;
			--lm1;
			unsigned n_swaps = 0;
			{
				difference_type delta = 0;
				if (len >= 1000) {
					delta = len / 2;
					m += delta;
					delta /= 2;
					n_swaps = sprout::detail::sort5<Compare>(first, first + delta, m, m + delta, lm1, comp);
				}
				else
				{
					delta = len / 2;
					m += delta;
					n_swaps = sprout::detail::sort3<Compare>(first, m, lm1, comp);
				}
			}
			iterator i = first;
			iterator j = lm1;
			if (!comp(*i, *m)) {
				while (true) {
					if (i == --j) {
						++i;
						j = last;
						if (!comp(*first, *--j)) {
							while (true) {
								if (i == j) {
									return true;
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
							return true;
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
						first = i;
						return false;
					}
					if (comp(*j, *m)) {
						sprout::swap(*i, *j);
						++n_swaps;
						break;
					}
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
					if (i > j) {
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
			if (n_swaps == 0) 	{
				bool fs = sprout::detail::insertion_sort_incomplete<Compare>(first, i, comp);
				if (sprout::detail::insertion_sort_incomplete<Compare>(i + 1, last, comp)) {
					if (fs) {
						return true;
					}
					last = i;
					return false;
				} else if (fs) {
					first = ++i;
					return false;
				}
			}
			if (i - first < last - i) {
				sprout::detail::sort<Compare>(first, i, comp);
				first = ++i;
			} else {
				sprout::detail::sort<Compare>(i + 1, last, comp);
				last = i;
			}
			return false;
		}
		template<typename Compare, typename RandomAccessIterator>
		inline SPROUT_CXX14_CONSTEXPR void
		sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			typedef typename std::add_lvalue_reference<RandomAccessIterator>::type iter_ref;
			while (!sprout::detail::sort_impl<Compare, iter_ref>(first, last, comp))
				;
		}
	}	// namespace detail
	//
	// 25.4.1.1 sort
	//
	template<typename RandomAccessIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		typedef typename std::add_lvalue_reference<Compare>::type compare_ref;
		sprout::detail::sort<compare_ref>(first, last, comp);
	}

	template<typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	sort(RandomAccessIterator first, RandomAccessIterator last) {
		sprout::sort(first, last, sprout::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CXX14_ALGORITHM_SORT_HPP
