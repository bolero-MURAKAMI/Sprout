/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_DETAIL_MIN_HPP
#define SPROUT_ALGORITHM_DETAIL_MIN_HPP

#include <sprout/config.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {

	// 25.4.7 Minimum and maximum
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR T const&
	min(T const& a, T const& b, Compare comp) {
		return comp(b, a) ? b : a;
	}

	template<typename T>
	inline SPROUT_CONSTEXPR T const&
	min(T const& a, T const& b) {
		return sprout::min(a, b, NS_SSCRISK_CEL_OR_SPROUT::less<T>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_DETAIL_MIN_HPP
