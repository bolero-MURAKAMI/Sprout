/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_INPLACE_MERGE_HPP
#define SPROUT_ALGORITHM_CXX14_INPLACE_MERGE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/iterator/advance.hpp>
#include <sprout/algorithm/lower_bound.hpp>
#include <sprout/algorithm/upper_bound.hpp>
#include <sprout/algorithm/cxx14/iter_swap.hpp>
#include <sprout/algorithm/cxx14/rotate.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename BidirectionalIterator, typename Distance, typename Compare>
		inline SPROUT_CXX14_CONSTEXPR void
		inplace_merge(
			BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last,
			Distance len1, Distance len2, Compare comp
			)
		{
			if (len1 == 0 || len2 == 0) {
				return;
			}
			if (len1 + len2 == 2) {
				if (comp(*middle, *first)) {
					sprout::iter_swap(first, middle);
				}
				return;
			}
			BidirectionalIterator first_cut = first;
			BidirectionalIterator second_cut = middle;
			Distance len11 = 0;
			Distance len22 = 0;
			if (len1 > len2) {
				len11 = len1 / 2;
				sprout::advance(first_cut, len11);
				second_cut = sprout::lower_bound(middle, last, *first_cut, comp);
				len22 = sprout::distance(middle, second_cut);
			} else {
				len22 = len2 / 2;
				sprout::advance(second_cut, len22);
				first_cut = sprout::upper_bound(first, middle, *second_cut, comp);
				len11 = sprout::distance(first, first_cut);
			}
			sprout::rotate(first_cut, middle, second_cut);
			BidirectionalIterator new_middle = first_cut;
			sprout::advance(new_middle, sprout::distance(middle, second_cut));
			sprout::detail::inplace_merge(first, first_cut, new_middle, len11, len22, comp);
			sprout::detail::inplace_merge(new_middle, second_cut, last, len1 - len11, len2 - len22, comp);
		}
	}	// namespace detail
	//
	// 25.4.4 Merge
	//
	template<typename BidirectionalIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR void
	inplace_merge(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Compare comp) {
		typedef typename std::iterator_traits<BidirectionalIterator>::difference_type difference_type;
		if (first == middle || middle == last) {
			return;
		}
		difference_type const len1 = sprout::distance(first, middle);
		difference_type const len2 = sprout::distance(middle, last);
		sprout::detail::inplace_merge(first, middle, last, len1, len2, comp);
	}

	template<typename BidirectionalIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	inplace_merge(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last) {
		sprout::inplace_merge(
			first, middle, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<BidirectionalIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_INPLACE_MERGE_HPP
