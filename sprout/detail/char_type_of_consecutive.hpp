/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_CHAR_TYPE_OF_CONSECUTIVE_HPP
#define SPROUT_DETAIL_CHAR_TYPE_OF_CONSECUTIVE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/detail/char_literal.hpp>

namespace sprout {
	namespace detail {
		template<typename CharType>
		struct is_char_type_of_consecutive_digits
			: public sprout::bool_constant<
				SPROUT_CHAR_LITERAL('0', CharType) + 1 == SPROUT_CHAR_LITERAL('1', CharType)
					&& SPROUT_CHAR_LITERAL('1', CharType) + 1 == SPROUT_CHAR_LITERAL('2', CharType)
					&& SPROUT_CHAR_LITERAL('2', CharType) + 1 == SPROUT_CHAR_LITERAL('3', CharType)
					&& SPROUT_CHAR_LITERAL('3', CharType) + 1 == SPROUT_CHAR_LITERAL('4', CharType)
					&& SPROUT_CHAR_LITERAL('4', CharType) + 1 == SPROUT_CHAR_LITERAL('5', CharType)
					&& SPROUT_CHAR_LITERAL('5', CharType) + 1 == SPROUT_CHAR_LITERAL('6', CharType)
					&& SPROUT_CHAR_LITERAL('6', CharType) + 1 == SPROUT_CHAR_LITERAL('7', CharType)
					&& SPROUT_CHAR_LITERAL('7', CharType) + 1 == SPROUT_CHAR_LITERAL('8', CharType)
					&& SPROUT_CHAR_LITERAL('8', CharType) + 1 == SPROUT_CHAR_LITERAL('9', CharType)
			>
		{};
		template<typename CharType>
		struct is_char_type_of_consecutive_digits<CharType const>
			: public sprout::detail::is_char_type_of_consecutive_digits<CharType>
		{};
		template<typename CharType>
		struct is_char_type_of_consecutive_digits<CharType volatile>
			: public sprout::detail::is_char_type_of_consecutive_digits<CharType>
		{};
		template<typename CharType>
		struct is_char_type_of_consecutive_digits<CharType const volatile>
			: public sprout::detail::is_char_type_of_consecutive_digits<CharType>
		{};

		template<typename CharType>
		struct is_char_type_of_consecutive_lower_alphabet
			: public sprout::bool_constant<
				SPROUT_CHAR_LITERAL('a', CharType) + 1 == SPROUT_CHAR_LITERAL('b', CharType)
					&& SPROUT_CHAR_LITERAL('b', CharType) + 1 == SPROUT_CHAR_LITERAL('c', CharType)
					&& SPROUT_CHAR_LITERAL('c', CharType) + 1 == SPROUT_CHAR_LITERAL('d', CharType)
					&& SPROUT_CHAR_LITERAL('d', CharType) + 1 == SPROUT_CHAR_LITERAL('e', CharType)
					&& SPROUT_CHAR_LITERAL('e', CharType) + 1 == SPROUT_CHAR_LITERAL('f', CharType)
					&& SPROUT_CHAR_LITERAL('f', CharType) + 1 == SPROUT_CHAR_LITERAL('g', CharType)
					&& SPROUT_CHAR_LITERAL('g', CharType) + 1 == SPROUT_CHAR_LITERAL('h', CharType)
					&& SPROUT_CHAR_LITERAL('h', CharType) + 1 == SPROUT_CHAR_LITERAL('i', CharType)
					&& SPROUT_CHAR_LITERAL('i', CharType) + 1 == SPROUT_CHAR_LITERAL('j', CharType)
					&& SPROUT_CHAR_LITERAL('j', CharType) + 1 == SPROUT_CHAR_LITERAL('k', CharType)
					&& SPROUT_CHAR_LITERAL('k', CharType) + 1 == SPROUT_CHAR_LITERAL('l', CharType)
					&& SPROUT_CHAR_LITERAL('l', CharType) + 1 == SPROUT_CHAR_LITERAL('m', CharType)
					&& SPROUT_CHAR_LITERAL('m', CharType) + 1 == SPROUT_CHAR_LITERAL('n', CharType)
					&& SPROUT_CHAR_LITERAL('n', CharType) + 1 == SPROUT_CHAR_LITERAL('o', CharType)
					&& SPROUT_CHAR_LITERAL('o', CharType) + 1 == SPROUT_CHAR_LITERAL('p', CharType)
					&& SPROUT_CHAR_LITERAL('p', CharType) + 1 == SPROUT_CHAR_LITERAL('q', CharType)
					&& SPROUT_CHAR_LITERAL('q', CharType) + 1 == SPROUT_CHAR_LITERAL('r', CharType)
					&& SPROUT_CHAR_LITERAL('r', CharType) + 1 == SPROUT_CHAR_LITERAL('s', CharType)
					&& SPROUT_CHAR_LITERAL('s', CharType) + 1 == SPROUT_CHAR_LITERAL('t', CharType)
					&& SPROUT_CHAR_LITERAL('t', CharType) + 1 == SPROUT_CHAR_LITERAL('u', CharType)
					&& SPROUT_CHAR_LITERAL('u', CharType) + 1 == SPROUT_CHAR_LITERAL('v', CharType)
					&& SPROUT_CHAR_LITERAL('v', CharType) + 1 == SPROUT_CHAR_LITERAL('w', CharType)
					&& SPROUT_CHAR_LITERAL('w', CharType) + 1 == SPROUT_CHAR_LITERAL('x', CharType)
					&& SPROUT_CHAR_LITERAL('x', CharType) + 1 == SPROUT_CHAR_LITERAL('y', CharType)
					&& SPROUT_CHAR_LITERAL('y', CharType) + 1 == SPROUT_CHAR_LITERAL('z', CharType)
			>
		{};
		template<typename CharType>
		struct is_char_type_of_consecutive_lower_alphabet<CharType const>
			: public sprout::detail::is_char_type_of_consecutive_lower_alphabet<CharType>
		{};
		template<typename CharType>
		struct is_char_type_of_consecutive_lower_alphabet<CharType volatile>
			: public sprout::detail::is_char_type_of_consecutive_lower_alphabet<CharType>
		{};
		template<typename CharType>
		struct is_char_type_of_consecutive_lower_alphabet<CharType const volatile>
			: public sprout::detail::is_char_type_of_consecutive_lower_alphabet<CharType>
		{};

		template<typename CharType>
		struct is_char_type_of_consecutive_upper_alphabet
			: public sprout::bool_constant<
				SPROUT_CHAR_LITERAL('A', CharType) + 1 == SPROUT_CHAR_LITERAL('B', CharType)
					&& SPROUT_CHAR_LITERAL('B', CharType) + 1 == SPROUT_CHAR_LITERAL('C', CharType)
					&& SPROUT_CHAR_LITERAL('C', CharType) + 1 == SPROUT_CHAR_LITERAL('D', CharType)
					&& SPROUT_CHAR_LITERAL('D', CharType) + 1 == SPROUT_CHAR_LITERAL('E', CharType)
					&& SPROUT_CHAR_LITERAL('E', CharType) + 1 == SPROUT_CHAR_LITERAL('F', CharType)
					&& SPROUT_CHAR_LITERAL('F', CharType) + 1 == SPROUT_CHAR_LITERAL('G', CharType)
					&& SPROUT_CHAR_LITERAL('G', CharType) + 1 == SPROUT_CHAR_LITERAL('H', CharType)
					&& SPROUT_CHAR_LITERAL('H', CharType) + 1 == SPROUT_CHAR_LITERAL('I', CharType)
					&& SPROUT_CHAR_LITERAL('I', CharType) + 1 == SPROUT_CHAR_LITERAL('J', CharType)
					&& SPROUT_CHAR_LITERAL('J', CharType) + 1 == SPROUT_CHAR_LITERAL('K', CharType)
					&& SPROUT_CHAR_LITERAL('K', CharType) + 1 == SPROUT_CHAR_LITERAL('L', CharType)
					&& SPROUT_CHAR_LITERAL('L', CharType) + 1 == SPROUT_CHAR_LITERAL('M', CharType)
					&& SPROUT_CHAR_LITERAL('M', CharType) + 1 == SPROUT_CHAR_LITERAL('N', CharType)
					&& SPROUT_CHAR_LITERAL('N', CharType) + 1 == SPROUT_CHAR_LITERAL('O', CharType)
					&& SPROUT_CHAR_LITERAL('O', CharType) + 1 == SPROUT_CHAR_LITERAL('P', CharType)
					&& SPROUT_CHAR_LITERAL('P', CharType) + 1 == SPROUT_CHAR_LITERAL('Q', CharType)
					&& SPROUT_CHAR_LITERAL('Q', CharType) + 1 == SPROUT_CHAR_LITERAL('R', CharType)
					&& SPROUT_CHAR_LITERAL('R', CharType) + 1 == SPROUT_CHAR_LITERAL('S', CharType)
					&& SPROUT_CHAR_LITERAL('S', CharType) + 1 == SPROUT_CHAR_LITERAL('T', CharType)
					&& SPROUT_CHAR_LITERAL('T', CharType) + 1 == SPROUT_CHAR_LITERAL('U', CharType)
					&& SPROUT_CHAR_LITERAL('U', CharType) + 1 == SPROUT_CHAR_LITERAL('V', CharType)
					&& SPROUT_CHAR_LITERAL('V', CharType) + 1 == SPROUT_CHAR_LITERAL('W', CharType)
					&& SPROUT_CHAR_LITERAL('W', CharType) + 1 == SPROUT_CHAR_LITERAL('X', CharType)
					&& SPROUT_CHAR_LITERAL('X', CharType) + 1 == SPROUT_CHAR_LITERAL('Y', CharType)
					&& SPROUT_CHAR_LITERAL('Y', CharType) + 1 == SPROUT_CHAR_LITERAL('Z', CharType)
			>
		{};
		template<typename CharType>
		struct is_char_type_of_consecutive_upper_alphabet<CharType const>
			: public sprout::detail::is_char_type_of_consecutive_upper_alphabet<CharType>
		{};
		template<typename CharType>
		struct is_char_type_of_consecutive_upper_alphabet<CharType volatile>
			: public sprout::detail::is_char_type_of_consecutive_upper_alphabet<CharType>
		{};
		template<typename CharType>
		struct is_char_type_of_consecutive_upper_alphabet<CharType const volatile>
			: public sprout::detail::is_char_type_of_consecutive_upper_alphabet<CharType>
		{};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_CHAR_TYPE_OF_CONSECUTIVE_HPP
