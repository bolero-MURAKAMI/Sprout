/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_IS_INCREASING_HPP
#define SPROUT_ALGORITHM_IS_INCREASING_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/algorithm/is_sorted.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// is_increasing
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR bool
	is_increasing(ForwardIterator first, ForwardIterator last) {
		return sprout::is_sorted(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_IS_INCREASING_HPP
