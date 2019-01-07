/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_ROTR_HPP
#define SPROUT_BIT_ROTR_HPP

#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/bit/shlr.hpp>

namespace sprout {
	//
	// rotr
	//
	template<typename Integral>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<Integral>::value,
		Integral
	>::type
	rotr(Integral x, int s) SPROUT_NOEXCEPT {
		return sprout::shlr(x, s) | (x << (sizeof(x) * CHAR_BIT - s));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_ROTR_HPP
