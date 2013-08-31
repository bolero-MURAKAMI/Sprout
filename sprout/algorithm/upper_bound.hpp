/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_UPPER_BOUND_HPP
#define SPROUT_ALGORITHM_UPPER_BOUND_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/detail/algorithm/upper_bound.hpp>

namespace sprout {

	// 25.4.3.2 upper_bound
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator, typename T, typename Compare>
	inline SPROUT_CONSTEXPR ForwardIterator
	upper_bound(ForwardIterator first, ForwardIterator last, T const& value, Compare comp) {
		return sprout::detail::upper_bound(first, sprout::distance(first, last), value, comp);
	}

	template<typename ForwardIterator, typename T>
	inline SPROUT_CONSTEXPR ForwardIterator
	upper_bound(ForwardIterator first, ForwardIterator last, T const& value) {
		return sprout::upper_bound(first, last, value, sprout::less<>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_UPPER_BOUND_HPP
