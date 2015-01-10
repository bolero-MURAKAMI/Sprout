/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CTYPE_MASK_HPP
#define SPROUT_CTYPE_MASK_HPP

#include <locale>
#include <sprout/config.hpp>

namespace sprout {
	namespace ctypes {
		//
		// mask_t
		//
		typedef std::ctype_base::mask mask_t;

		//
		// space
		// print
		// cntrl
		// upper
		// lower
		// alpha
		// digit
		// punct
		// xdigit
		// blank
		// alnum
		// graph
		//
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t space = std::ctype_base::space;
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t print = std::ctype_base::print;
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t cntrl = std::ctype_base::cntrl;
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t upper = std::ctype_base::upper;
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t lower = std::ctype_base::lower;
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t alpha = std::ctype_base::alpha;
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t digit = std::ctype_base::digit;
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t punct = std::ctype_base::punct;
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t xdigit = std::ctype_base::xdigit;
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t blank = /*std::ctype_base::blank*/1 << 9;
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t alnum = std::ctype_base::alnum;
		SPROUT_STATIC_CONSTEXPR sprout::ctypes::mask_t graph = std::ctype_base::graph;
	}	// namespace ctypes
}	// namespace sprout

#endif	// #ifndef SPROUT_CTYPE_MASK_HPP
