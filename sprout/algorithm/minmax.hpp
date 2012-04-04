#ifndef SPROUT_ALGORITHM_MINMAX_HPP
#define SPROUT_ALGORITHM_MINMAX_HPP

#include <sprout/config.hpp>
#include <sprout/utility/pair.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.4.7 Minimum and maximum
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR sprout::pair<T, T> minmax(T const& a, T const& b, Compare comp) {
		return comp(b, a) ? sprout::pair<T, T>(b, a) : sprout::pair<T, T>(a, b);
	}

	template<typename T>
	inline SPROUT_CONSTEXPR sprout::pair<T, T> minmax(T const& a, T const& b) {
		return sprout::minmax(a, b, NS_SSCRISK_CEL_OR_SPROUT::less<T>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MINMAX_HPP
