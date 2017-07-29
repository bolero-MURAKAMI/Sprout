/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_NUMERIC_UINT_HPP
#define SPROUT_WEED_PARSER_NUMERIC_UINT_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/integer/integer_digits.hpp>
#include <sprout/weed/parser/numeric/uint_p.hpp>

namespace sprout {
	namespace weed {
		//
		// uint_
		//
		SPROUT_STATIC_CONSTEXPR auto uint_ = sprout::weed::uint_p<std::uintmax_t, 10, 1, static_cast<std::size_t>(-1)>();

		//
		// uint8
		// uint16
		// uint32
		// uint64
		//
		SPROUT_STATIC_CONSTEXPR auto uint8 = sprout::weed::uint_p<std::uint8_t, 10>();
		SPROUT_STATIC_CONSTEXPR auto uint16 = sprout::weed::uint_p<std::uint16_t, 10>();
		SPROUT_STATIC_CONSTEXPR auto uint32 = sprout::weed::uint_p<std::uint32_t, 10>();
		SPROUT_STATIC_CONSTEXPR auto uint64 = sprout::weed::uint_p<std::uint64_t, 10>();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_NUMERIC_UINT_HPP
