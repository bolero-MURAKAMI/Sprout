/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_PREV_PERMUTATION_HPP
#define SPROUT_ALGORITHM_CXX14_PREV_PERMUTATION_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/algorithm/cxx14/reverse.hpp>
#include <sprout/utility/swap.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename Compare, typename BidirectionalIterator>
		inline SPROUT_CXX14_CONSTEXPR bool
		prev_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare comp) {
			BidirectionalIterator i = last;
			if (first == last || first == --i) {
				return false;
			}
			while (true) {
				BidirectionalIterator ip1 = i;
				if (comp(*ip1, *--i)) {
					BidirectionalIterator j = last;
					while (!comp(*--j, *i))
						;
					sprout::swap(*i, *j);
					sprout::reverse(ip1, last);
					return true;
				}
				if (i == first) {
					sprout::reverse(first, last);
					return false;
				}
			}
		}
	}	// namespace detail
	//
	// 25.4.9 Permutation generators
	//
	template<typename BidirectionalIterator, typename Compare>
	inline SPROUT_CXX14_CONSTEXPR bool
	prev_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare comp) {
		typedef typename std::add_lvalue_reference<Compare>::type compare_ref;
		return sprout::detail::prev_permutation<compare_ref>(first, last, comp);
	}

	template<typename BidirectionalIterator>
	inline SPROUT_CXX14_CONSTEXPR bool
	prev_permutation(BidirectionalIterator first, BidirectionalIterator last) {
		return sprout::prev_permutation(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<BidirectionalIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_PREV_PERMUTATION_HPP
