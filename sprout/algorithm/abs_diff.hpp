/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_ABS_DIFF_HPP
#define SPROUT_ALGORITHM_ABS_DIFF_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// abs_diff
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T
	abs_diff(T const& a, T const& b) {
		return (a < b) ? b - a : a - b;
	}
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR T
	abs_diff(T const& a, T const& b, Compare comp) {
		return comp(a, b) ? b - a : a - b;
	}
	template<typename T, typename Compare, typename Difference>
	inline SPROUT_CONSTEXPR T
	abs_diff(T const& a, T const& b, Compare comp, Difference diff) {
		return comp(a, b) ? diff(b, a) : diff(a, b);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_ABS_DIFF_HPP
