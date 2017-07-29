/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_NUMERIC_BIN_HPP
#define SPROUT_WEED_PARSER_NUMERIC_BIN_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/integer/integer_digits.hpp>
#include <sprout/weed/parser/numeric/uint_p.hpp>

namespace sprout {
	namespace weed {
		//
		// bin
		//
		SPROUT_STATIC_CONSTEXPR auto bin = sprout::weed::uint_p<std::uintmax_t, 2, static_cast<std::size_t>(-1)>();

		//
		// bin8
		// bin16
		// bin32
		// bin64
		//
		SPROUT_STATIC_CONSTEXPR auto bin8 = sprout::weed::uint_p<std::uint8_t, 2>();
		SPROUT_STATIC_CONSTEXPR auto bin16 = sprout::weed::uint_p<std::uint16_t, 2>();
		SPROUT_STATIC_CONSTEXPR auto bin32 = sprout::weed::uint_p<std::uint32_t, 2>();
		SPROUT_STATIC_CONSTEXPR auto bin64 = sprout::weed::uint_p<std::uint64_t, 2>();

		//
		// bin8f
		// bin16f
		// bin32f
		// bin64f
		//
		SPROUT_STATIC_CONSTEXPR auto bin8f = sprout::weed::uint_p<std::uint8_t, 2, sprout::integer_digits<std::uint8_t, 2>::value>();
		SPROUT_STATIC_CONSTEXPR auto bin16f = sprout::weed::uint_p<std::uint16_t, 2, sprout::integer_digits<std::uint16_t, 2>::value>();
		SPROUT_STATIC_CONSTEXPR auto bin32f = sprout::weed::uint_p<std::uint32_t, 2, sprout::integer_digits<std::uint32_t, 2>::value>();
		SPROUT_STATIC_CONSTEXPR auto bin64f = sprout::weed::uint_p<std::uint64_t, 2, sprout::integer_digits<std::uint64_t, 2>::value>();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_NUMERIC_BIN_HPP
