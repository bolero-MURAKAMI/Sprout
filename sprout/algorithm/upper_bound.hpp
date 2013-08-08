/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_UPPER_BOUND_HPP
#define SPROUT_ALGORITHM_UPPER_BOUND_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {

	// 25.4.3.2 upper_bound
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator, typename T, typename Compare>
	inline SPROUT_CONSTEXPR ForwardIterator
	upper_bound(ForwardIterator first, ForwardIterator last, T const& value, Compare comp) {
		return first == last ? last
			: sprout::next(first) == last ? !comp(value, *first) ? last : first
			: !comp(value, *sprout::next(first, sprout::distance(first, last) / 2))
				? sprout::upper_bound(sprout::next(first, sprout::distance(first, last) / 2), last, value, comp)
			: sprout::upper_bound(first, sprout::next(first, sprout::distance(first, last) / 2), value, comp)
			;
	}

	template<typename ForwardIterator, typename T>
	inline SPROUT_CONSTEXPR ForwardIterator
	upper_bound(ForwardIterator first, ForwardIterator last, T const& value) {
		return sprout::upper_bound(
			first, last, value,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_UPPER_BOUND_HPP
