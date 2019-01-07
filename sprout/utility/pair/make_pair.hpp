/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_PAIR_MAKE_PAIR_HPP
#define SPROUT_UTILITY_PAIR_MAKE_PAIR_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/functional/ref.hpp>

namespace sprout {
	//
	// make_pair
	//
	template<typename T1, typename T2>
	inline SPROUT_CONSTEXPR sprout::pair<
		typename sprout::strip_reference<typename std::decay<T1>::type>::type,
		typename sprout::strip_reference<typename std::decay<T2>::type>::type
	>
	make_pair(T1&& x, T2&& y) {
		return sprout::pair<
			typename sprout::strip_reference<typename std::decay<T1>::type>::type,
			typename sprout::strip_reference<typename std::decay<T2>::type>::type
		>(
			SPROUT_FORWARD(T1, x),
			SPROUT_FORWARD(T2, y)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_MAKE_PAIR_HPP
