/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CLAMP_HPP
#define SPROUT_ALGORITHM_CLAMP_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// clamp
	//
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR T const&
	clamp(T const& value, typename sprout::identity<T>::type const& low, typename sprout::identity<T>::type const& high, Compare comp) {
		return comp(value, low) ? low
			: comp(high, value) ? high
			: value
			;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR T const&
	clamp(T const& value, typename sprout::identity<T>::type const& low, typename sprout::identity<T>::type const& high) {
		return sprout::clamp(
			value, low, high,
			NS_SSCRISK_CEL_OR_SPROUT::less<T>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CLAMP_HPP
