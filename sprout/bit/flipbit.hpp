/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_FLIPBIT_HPP
#define SPROUT_BIT_FLIPBIT_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// flipbit
	//
	template<typename Integral>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<Integral>::value,
		Integral
	>::type
	flipbit(Integral x, int b) SPROUT_NOEXCEPT {
		return x ^ (Integral(1) << b);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_FLIPBIT_HPP
