/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_NUMERIC_HEX_HPP
#define SPROUT_WEED_PARSER_NUMERIC_HEX_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/integer/integer_digits.hpp>
#include <sprout/weed/parser/numeric/uint_p.hpp>

namespace sprout {
	namespace weed {
		//
		// hex
		//
		SPROUT_STATIC_CONSTEXPR auto hex = sprout::weed::uint_p<std::uintmax_t, 16, static_cast<std::size_t>(-1)>();

		//
		// hex8
		// hex16
		// hex32
		// hex64
		//
		SPROUT_STATIC_CONSTEXPR auto hex8 = sprout::weed::uint_p<std::uint8_t, 16>();
		SPROUT_STATIC_CONSTEXPR auto hex16 = sprout::weed::uint_p<std::uint16_t, 16>();
		SPROUT_STATIC_CONSTEXPR auto hex32 = sprout::weed::uint_p<std::uint32_t, 16>();
		SPROUT_STATIC_CONSTEXPR auto hex64 = sprout::weed::uint_p<std::uint64_t, 16>();

		//
		// hex8f
		// hex16f
		// hex32f
		// hex64f
		//
		SPROUT_STATIC_CONSTEXPR auto hex8f = sprout::weed::uint_p<std::uint8_t, 16, sprout::integer_digits<std::uint8_t, 16>::value>();
		SPROUT_STATIC_CONSTEXPR auto hex16f = sprout::weed::uint_p<std::uint16_t, 16, sprout::integer_digits<std::uint16_t, 16>::value>();
		SPROUT_STATIC_CONSTEXPR auto hex32f = sprout::weed::uint_p<std::uint32_t, 16, sprout::integer_digits<std::uint32_t, 16>::value>();
		SPROUT_STATIC_CONSTEXPR auto hex64f = sprout::weed::uint_p<std::uint64_t, 16, sprout::integer_digits<std::uint64_t, 16>::value>();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_NUMERIC_HEX_HPP
