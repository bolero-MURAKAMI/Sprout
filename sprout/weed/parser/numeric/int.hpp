/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_NUMERIC_INT_HPP
#define SPROUT_WEED_PARSER_NUMERIC_INT_HPP

#include <cstddef>
#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/integer/integer_digits.hpp>
#include <sprout/weed/parser/numeric/int_p.hpp>

namespace sprout {
	namespace weed {
		//
		// int_
		//
		SPROUT_STATIC_CONSTEXPR auto int_ = sprout::weed::int_p<std::intmax_t, 10, 1, static_cast<std::size_t>(-1)>();

		//
		// int8
		// int16
		// int32
		// int64
		//
		SPROUT_STATIC_CONSTEXPR auto int8 = sprout::weed::int_p<std::int8_t, 10>();
		SPROUT_STATIC_CONSTEXPR auto int16 = sprout::weed::int_p<std::int16_t, 10>();
		SPROUT_STATIC_CONSTEXPR auto int32 = sprout::weed::int_p<std::int32_t, 10>();
		SPROUT_STATIC_CONSTEXPR auto int64 = sprout::weed::int_p<std::int64_t, 10>();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_NUMERIC_INT_HPP
