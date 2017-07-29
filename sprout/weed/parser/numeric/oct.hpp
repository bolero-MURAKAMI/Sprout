/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_NUMERIC_OCT_HPP
#define SPROUT_WEED_PARSER_NUMERIC_OCT_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/integer/integer_digits.hpp>
#include <sprout/weed/parser/numeric/uint_p.hpp>

namespace sprout {
	namespace weed {
		//
		// oct
		//
		SPROUT_STATIC_CONSTEXPR auto oct = sprout::weed::uint_p<std::uintmax_t, 8, static_cast<std::size_t>(-1)>();

		//
		// oct8
		// oct16
		// oct32
		// oct64
		//
		SPROUT_STATIC_CONSTEXPR auto oct8 = sprout::weed::uint_p<std::uint8_t, 8>();
		SPROUT_STATIC_CONSTEXPR auto oct16 = sprout::weed::uint_p<std::uint16_t, 8>();
		SPROUT_STATIC_CONSTEXPR auto oct32 = sprout::weed::uint_p<std::uint32_t, 8>();
		SPROUT_STATIC_CONSTEXPR auto oct64 = sprout::weed::uint_p<std::uint64_t, 8>();

		//
		// oct8f
		// oct16f
		// oct32f
		// oct64f
		//
		SPROUT_STATIC_CONSTEXPR auto oct8f = sprout::weed::uint_p<std::uint8_t, 8, sprout::integer_digits<std::uint8_t, 8>::value>();
		SPROUT_STATIC_CONSTEXPR auto oct16f = sprout::weed::uint_p<std::uint16_t, 8, sprout::integer_digits<std::uint16_t, 8>::value>();
		SPROUT_STATIC_CONSTEXPR auto oct32f = sprout::weed::uint_p<std::uint32_t, 8, sprout::integer_digits<std::uint32_t, 8>::value>();
		SPROUT_STATIC_CONSTEXPR auto oct64f = sprout::weed::uint_p<std::uint64_t, 8, sprout::integer_digits<std::uint64_t, 8>::value>();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_NUMERIC_OCT_HPP
