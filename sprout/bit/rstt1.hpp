/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_RSTT1_HPP
#define SPROUT_BIT_RSTT1_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// rstt1
	//
	template<typename Integral>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<Integral>::value,
		Integral
	>::type
	rstt1(Integral x) SPROUT_NOEXCEPT {
		return x & (x + 1);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_RSTT1_HPP
