/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_CHAR_CONVERSION_HPP
#define SPROUT_DETAIL_CHAR_CONVERSION_HPP

#include <cstddef>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/ctype/ascii.hpp>
#include <sprout/assert.hpp>

namespace sprout {
	namespace detail {
		template<typename Elem, typename IntType>
		inline SPROUT_CONSTEXPR Elem
		int_to_char(IntType val, int base) {
			return SPROUT_ASSERT(2 <= base && base <= 36), SPROUT_ASSERT(IntType(0) <= val && val < static_cast<IntType>(base)),
				val < 10 ? static_cast<Elem>('0') + val
					: static_cast<Elem>('a') + (val - 10)
				;
		}
		template<typename Elem, typename IntType>
		inline SPROUT_CONSTEXPR Elem
		int_to_char(IntType val) {
			return SPROUT_ASSERT(IntType(0) <= val && val < IntType(10)),
				static_cast<Elem>('0') + val
				;
		}

		template<typename IntType, typename Elem>
		inline SPROUT_CONSTEXPR IntType
		char_to_int(Elem c, int base) {
			return sprout::ascii::isdigit(c) && c - static_cast<Elem>('0') < base ? c - static_cast<Elem>('0')
				: sprout::ascii::islower(c) && c - static_cast<Elem>('a') + 10 < base ? c - static_cast<Elem>('a') + 10
				: sprout::ascii::isupper(c) && c - static_cast<Elem>('A') + 10 < base ? c - static_cast<Elem>('A') + 10
				: static_cast<IntType>(-1)
				;
		}
		template<typename IntType, typename Elem>
		inline SPROUT_CONSTEXPR IntType
		char_to_int(Elem c) {
			return sprout::ascii::isdigit(c) ? c - static_cast<Elem>('0')
				: static_cast<IntType>(-1)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_CHAR_CONVERSION_HPP
