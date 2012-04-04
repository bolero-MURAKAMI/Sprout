#ifndef SPROUT_ALGORITHM_MAX_HPP
#define SPROUT_ALGORITHM_MAX_HPP

#include <sprout/config.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.7 Minimum and maximum
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR T const& max(T const& a, T const& b, Compare comp) {
		return comp(a, b) ? b : a;
	}

	template<typename T>
	inline SPROUT_CONSTEXPR T const& max(T const& a, T const& b) {
		return sprout::max(a, b, NS_SSCRISK_CEL_OR_SPROUT::less<T>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MAX_HPP
