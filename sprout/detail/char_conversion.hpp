/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_CHAR_CONVERSION_HPP
#define SPROUT_DETAIL_CHAR_CONVERSION_HPP

#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/ctype/ascii.hpp>
#include <sprout/assert.hpp>
#include <sprout/static_assert.hpp>
#include <sprout/detail/char_literal.hpp>
#include <sprout/detail/char_type_of_consecutive.hpp>

namespace sprout {
	namespace detail {
		template<typename Elem, typename IntType>
		inline SPROUT_CONSTEXPR Elem
		int_to_char(IntType val, int base) {
			SPROUT_STATIC_ASSERT(sprout::detail::is_char_type_of_consecutive_digits<Elem>::value);
			SPROUT_STATIC_ASSERT(sprout::detail::is_char_type_of_consecutive_lower_alphabet<Elem>::value);
			return SPROUT_ASSERT(2 <= base && base <= 36), SPROUT_ASSERT(IntType(0) <= val && val < static_cast<IntType>(base)),
				val < 10 ? SPROUT_CHAR_LITERAL('0', Elem) + val
					: SPROUT_CHAR_LITERAL('a', Elem) + (val - 10)
				;
		}
		template<typename Elem, typename IntType>
		inline SPROUT_CONSTEXPR Elem
		int_to_char(IntType val) {
			SPROUT_STATIC_ASSERT(sprout::detail::is_char_type_of_consecutive_digits<Elem>::value);
			return SPROUT_ASSERT(IntType(0) <= val && val < IntType(10)),
				SPROUT_CHAR_LITERAL('0', Elem) + val
				;
		}

		template<typename IntType, typename Elem>
		inline SPROUT_CONSTEXPR IntType
		char_to_int(Elem c, int base) {
			SPROUT_STATIC_ASSERT(sprout::detail::is_char_type_of_consecutive_digits<Elem>::value);
			SPROUT_STATIC_ASSERT(sprout::detail::is_char_type_of_consecutive_lower_alphabet<Elem>::value);
			SPROUT_STATIC_ASSERT(sprout::detail::is_char_type_of_consecutive_upper_alphabet<Elem>::value);
			return sprout::ascii::isdigit(c) && c - SPROUT_CHAR_LITERAL('0', Elem) < base ? c - SPROUT_CHAR_LITERAL('0', Elem)
				: sprout::ascii::islower(c) && c - SPROUT_CHAR_LITERAL('a', Elem) + 10 < base ? c - SPROUT_CHAR_LITERAL('a', Elem) + 10
				: sprout::ascii::isupper(c) && c - SPROUT_CHAR_LITERAL('A', Elem) + 10 < base ? c - SPROUT_CHAR_LITERAL('A', Elem) + 10
				: static_cast<IntType>(-1)
				;
		}
		template<typename IntType, typename Elem>
		inline SPROUT_CONSTEXPR IntType
		char_to_int(Elem c) {
			SPROUT_STATIC_ASSERT(sprout::detail::is_char_type_of_consecutive_digits<Elem>::value);
			return sprout::ascii::isdigit(c) ? c - SPROUT_CHAR_LITERAL('0', Elem)
				: static_cast<IntType>(-1)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_CHAR_CONVERSION_HPP
