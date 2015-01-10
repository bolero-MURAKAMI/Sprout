/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_ROTL_HPP
#define SPROUT_BIT_ROTL_HPP

#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/bit/shlr.hpp>

namespace sprout {
	//
	// rotl
	//
	template<typename Integral>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<Integral>::value,
		Integral
	>::type
	rotl(Integral x, int s) SPROUT_NOEXCEPT {
		return (x << s) | sprout::shlr(x, sizeof(x) * CHAR_BIT - s);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_ROTL_HPP
