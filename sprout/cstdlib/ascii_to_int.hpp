/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDLIB_DECIMAL_TO_INT_HPP
#define SPROUT_CSTDLIB_DECIMAL_TO_INT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/type_traits/is_signed.hpp>
#include <sprout/type_traits/is_unsigned.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/ctype/ascii.hpp>
#include <sprout/static_assert.hpp>
#include <sprout/detail/char_literal.hpp>
#include <sprout/detail/char_type_of_consecutive.hpp>

namespace sprout {
	namespace detail {
		// Copyright (c) 2011 osyo-manga : http://d.hatena.ne.jp/osyo-manga/

		template<typename IntType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR IntType
		ascii_to_int_impl(NullTerminatedIterator const& str, IntType val, bool negative) {
			typedef typename std::iterator_traits<NullTerminatedIterator>::value_type value_type;
			SPROUT_STATIC_ASSERT(sprout::detail::is_char_type_of_consecutive_digits<value_type>::value);
			return !sprout::ascii::isdigit(*str)
				? negative ? -val : val
				: val > (sprout::numeric_limits<IntType>::max() - (*str - SPROUT_CHAR_LITERAL('0', value_type)) - (negative ? 1 : 0)) / 10
				? (negative ? sprout::numeric_limits<IntType>::min() : sprout::numeric_limits<IntType>::max())
				: sprout::detail::ascii_to_int_impl<IntType>(
					sprout::next(str),
					val * 10 + (*str - SPROUT_CHAR_LITERAL('0', value_type)),
					negative
					)
				;
		}
		template<typename IntType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_unsigned<IntType>::value,
			IntType
		>::type
		ascii_to_int(NullTerminatedIterator const& str) {
			typedef typename std::iterator_traits<NullTerminatedIterator>::value_type value_type;
			return sprout::ascii::isspace(*str)
				? sprout::detail::ascii_to_int<IntType>(sprout::next(str))
				: *str == SPROUT_CHAR_LITERAL('+', value_type)
				? sprout::detail::ascii_to_int_impl<IntType>(sprout::next(str), IntType(), false)
				: sprout::detail::ascii_to_int_impl<IntType>(str, IntType(), false)
				;
		}
		template<typename IntType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_signed<IntType>::value,
			IntType
		>::type
		ascii_to_int(NullTerminatedIterator const& str) {
			typedef typename std::iterator_traits<NullTerminatedIterator>::value_type value_type;
			return sprout::ascii::isspace(*str)
				? sprout::detail::ascii_to_int<IntType>(sprout::next(str))
				: *str == SPROUT_CHAR_LITERAL('-', value_type)
				? sprout::detail::ascii_to_int_impl<IntType>(sprout::next(str), IntType(), true)
				: *str == SPROUT_CHAR_LITERAL('+', value_type)
				? sprout::detail::ascii_to_int_impl<IntType>(sprout::next(str), IntType(), false)
				: sprout::detail::ascii_to_int_impl<IntType>(str, IntType(), false)
				;
		}
	}	// namespace detail

	//
	// ascii_to_int
	//
	template<typename IntType, typename Char>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<IntType>::value,
		IntType
	>::type
	ascii_to_int(Char const* str) {
		return sprout::detail::ascii_to_int<IntType>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_DECIMAL_TO_INT_HPP
