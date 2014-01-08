/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_PAIR_COMPARISON_HPP
#define SPROUT_UTILITY_PAIR_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	template<typename T1, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return x.first == y.first && x.second == y.second;
	}
	template<typename T1, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return !(x == y);
	}
	template<typename T1, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return ((x.first) < (y.first)) || (!((y.first) < (x.first)) && ((x.second) < (y.second)));
	}
	template<typename T1, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return y < x;
	}
	template<typename T1, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return !(y < x);
	}
	template<typename T1, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return !(x < y);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_COMPARISON_HPP
