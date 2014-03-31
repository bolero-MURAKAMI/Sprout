/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BIT_SHAR_HPP
#define SPROUT_BIT_SHAR_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// shar
	//
	template<typename Integral>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<Integral>::value,
		Integral
	>::type
	shar(Integral x, int s) SPROUT_NOEXCEPT {
		typedef typename std::make_signed<Integral>::type type;
		return static_cast<Integral>(static_cast<type>(x) >> s);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_BIT_SHAR_HPP
