/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CTYPE_MASK_HPP
#define SPROUT_CTYPE_MASK_HPP

#include <locale>
#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>

namespace sprout {
	namespace ctypes {
		//
		// mask
		//
		enum mask {
			space = std::ctype_base::space,
			print = std::ctype_base::print,
			cntrl = std::ctype_base::cntrl,
			upper = std::ctype_base::upper,
			lower = std::ctype_base::lower,
			alpha = std::ctype_base::alpha,
			digit = std::ctype_base::digit,
			punct = std::ctype_base::punct,
			xdigit = std::ctype_base::xdigit,
#if SPROUT_GCC_EARLIER(5, 0, 0)
			blank = 0x0001,
#else	// #if SPROUT_GCC_EARLIER(5, 0, 0)
			blank = std::ctype_base::blank,
#endif	// #if SPROUT_GCC_EARLIER(5, 0, 0)
			alnum = std::ctype_base::alnum,
			graph = std::ctype_base::graph
		};
		inline SPROUT_CONSTEXPR sprout::ctypes::mask
		operator&(sprout::ctypes::mask x, sprout::ctypes::mask y) {
			return sprout::ctypes::mask(static_cast<int>(x) & static_cast<int>(y));
		}
		inline SPROUT_CONSTEXPR sprout::ctypes::mask
		operator|(sprout::ctypes::mask x, sprout::ctypes::mask y) {
			return sprout::ctypes::mask(static_cast<int>(x) | static_cast<int>(y));
		}
		inline SPROUT_CONSTEXPR sprout::ctypes::mask
		operator^(sprout::ctypes::mask x, sprout::ctypes::mask y) {
			return sprout::ctypes::mask(static_cast<int>(x) ^ static_cast<int>(y));
		}
		inline SPROUT_CONSTEXPR sprout::ctypes::mask
		operator~(sprout::ctypes::mask x) {
			return sprout::ctypes::mask(~static_cast<int>(x));
		}
		inline SPROUT_CXX14_CONSTEXPR sprout::ctypes::mask&
		operator&=(sprout::ctypes::mask& x, sprout::ctypes::mask y) {
			return x = x & y;
		}
		inline SPROUT_CXX14_CONSTEXPR sprout::ctypes::mask&
		operator|=(sprout::ctypes::mask& x, sprout::ctypes::mask y) {
			return x = x | y;
		}
		inline SPROUT_CXX14_CONSTEXPR sprout::ctypes::mask&
		operator^=(sprout::ctypes::mask& x, sprout::ctypes::mask y) {
			return x = x ^ y;
		}
	}	// namespace ctypes
}	// namespace sprout

#endif	// #ifndef SPROUT_CTYPE_MASK_HPP
