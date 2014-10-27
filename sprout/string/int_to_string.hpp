/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_INT_TO_STRING_HPP
#define SPROUT_STRING_INT_TO_STRING_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/string/string.hpp>
#include <sprout/integer/integer_digits.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/detail/char_literal.hpp>
#include <sprout/detail/char_conversion.hpp>
#include <sprout/detail/math/int.hpp>

namespace sprout {
	//
	// printed_integer_digits
	//
	template<typename IntType, std::size_t Base = 10>
	struct printed_integer_digits
		: public sprout::integral_constant<
			std::size_t,
			sprout::integer_digits<IntType, Base>::value + (std::is_signed<IntType>::value ? 1 : 0)
		>
	{};

	namespace detail {
		template<
			typename Elem, int Base, typename IntType,
			sprout::index_t... Indexes,
			typename sprout::enabler_if<std::is_signed<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_integer_digits<IntType, Base>::value>
		int_to_string(IntType val, int digits, sprout::index_tuple<Indexes...>) {
			typedef sprout::detail::string_construct_access<Elem, sprout::printed_integer_digits<IntType, Base>::value> access_type;
			return val < 0 ? access_type::raw_construct(
					static_cast<std::size_t>(digits + 1),
					SPROUT_CHAR_LITERAL('-', Elem),
					(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at<Base>(val, digits - 1 - Indexes))
						: Elem()
						)...
					)
				: access_type::raw_construct(
					static_cast<std::size_t>(digits),
					(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at<Base>(val, digits - 1 - Indexes))
						: Elem()
						)...
					)
				;
		}
		template<
			typename Elem, int Base, typename IntType,
			sprout::index_t... Indexes,
			typename sprout::enabler_if<std::is_unsigned<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_integer_digits<IntType, Base>::value>
		int_to_string(IntType val, int digits, sprout::index_tuple<Indexes...>) {
			typedef sprout::detail::string_construct_access<Elem, sprout::printed_integer_digits<IntType, Base>::value> access_type;
			return access_type::raw_construct(
				static_cast<std::size_t>(digits),
				(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at<Base>(val, digits - 1 - Indexes))
					: Elem()
					)...
				);
		}
	}	// namespace detail

	//
	// int_to_string
	//
	template<
		typename Elem, int Base = 10, typename IntType,
		typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_integer_digits<IntType, Base>::value>
	int_to_string(IntType val) {
		return sprout::detail::int_to_string<Elem, Base>(
			val,
			sprout::detail::int_digits<Base>(val),
			sprout::make_index_tuple<sprout::integer_digits<IntType, Base>::value>::make()
			);
	}

	//
	// to_string_of
	//
	template<
		typename Elem, typename IntType,
		typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_integer_digits<IntType, 10>::value>
	to_string_of(IntType val) {
		return sprout::int_to_string<Elem, 10>(val);
	}

	//
	// to_string
	//
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_integer_digits<IntType>::value>
	to_string(IntType val) {
		return sprout::to_string_of<char>(val);
	}

	//
	// to_wstring
	//
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_integer_digits<IntType>::value>
	to_wstring(IntType val) {
		return sprout::to_string_of<wchar_t>(val);
	}

	//
	// to_u16string
	//
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_integer_digits<IntType>::value>
	to_u16string(IntType val) {
		return sprout::to_string_of<char16_t>(val);
	}

	//
	// to_u32string
	//
	template<typename IntType, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_integer_digits<IntType>::value>
	to_u32string(IntType val) {
		return sprout::to_string_of<char32_t>(val);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_INT_TO_STRING_HPP
