/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_CNTT1_HPP
#define SPROUT_BIT_CNTT1_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/bit/ctz.hpp>

namespace sprout {
	//
	// cntt1
	//
	template<typename Integral>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<Integral>::value,
		int
	>::type
	cntt1(Integral x) SPROUT_NOEXCEPT {
		return sprout::ctz(~x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_CNTT1_HPP
