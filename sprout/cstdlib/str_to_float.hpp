/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDLIB_STR_TO_FLOAT_HPP
#define SPROUT_CSTDLIB_STR_TO_FLOAT_HPP

#include <cstdlib>
#include <cmath>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/ctype/ascii.hpp>
#include <sprout/detail/char_literal.hpp>
#include <sprout/detail/char_type_of_consecutive.hpp>

namespace sprout {
	namespace detail {
		template<typename FloatType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR FloatType
		str_to_float_impl_scale(
			NullTerminatedIterator const& str,
			bool negative,
			FloatType number = FloatType(),
			std::size_t num_digits = 0,
			std::size_t num_decimals = 0,
			long exponent = 0,
			long n = 0,
			FloatType p10 = FloatType(10)
			)
		{
			return n ? sprout::detail::str_to_float_impl_scale<FloatType>(
					str,
					negative,
					n & 1 ? (exponent < 0 ? number / p10 : number * p10) : number,
					num_digits,
					num_decimals,
					exponent,
					n >> 1,
					p10 * p10
					)
				: number
				;
		}
		template<typename FloatType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR FloatType
		str_to_float_impl_exponent_2(
			NullTerminatedIterator const& str,
			bool negative,
			FloatType number = FloatType(),
			std::size_t num_digits = 0,
			std::size_t num_decimals = 0,
			long exponent = 0
			)
		{
			return exponent >= sprout::numeric_limits<FloatType>::min_exponent
				&& exponent <= sprout::numeric_limits<FloatType>::max_exponent
				? sprout::detail::str_to_float_impl_scale<FloatType>(
					str,
					negative,
					number,
					num_digits,
					num_decimals,
					exponent,
					exponent < 0 ? -exponent : exponent
					)
				: HUGE_VAL
				;
		}
		template<typename FloatType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR FloatType
		str_to_float_impl_exponent_1(
			NullTerminatedIterator const& str,
			bool negative,
			FloatType number = FloatType(),
			std::size_t num_digits = 0,
			std::size_t num_decimals = 0,
			long exponent = 0,
			long n = 0
			)
		{
			typedef typename std::iterator_traits<NullTerminatedIterator>::value_type char_type;
			SPROUT_STATIC_ASSERT(sprout::detail::is_char_type_of_consecutive_digits<char_type>::value);
			return sprout::ascii::isdigit(*str) ? sprout::detail::str_to_float_impl_exponent_1<FloatType>(
					sprout::next(str),
					negative,
					number,
					num_digits,
					num_decimals,
					exponent,
					n * 10 + (*str - SPROUT_CHAR_LITERAL('0', char_type))
					)
				: sprout::detail::str_to_float_impl_exponent_2<FloatType>(
					str,
					negative,
					number,
					num_digits,
					num_decimals,
					negative ? exponent + n : exponent - n
					)
				;
		}
		template<typename FloatType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR FloatType
		str_to_float_impl_exponent(
			NullTerminatedIterator const& str,
			bool negative,
			FloatType number = FloatType(),
			std::size_t num_digits = 0,
			std::size_t num_decimals = 0,
			long exponent = 0
			)
		{
			typedef typename std::iterator_traits<NullTerminatedIterator>::value_type char_type;
			return (*str == SPROUT_CHAR_LITERAL('e', char_type) || *str == SPROUT_CHAR_LITERAL('E', char_type))
				? *sprout::next(str) == SPROUT_CHAR_LITERAL('-', char_type)
					? sprout::detail::str_to_float_impl_exponent_1<FloatType>(
						sprout::next(str, 2),
						true,
						number,
						num_digits,
						num_decimals,
						exponent
						)
					: sprout::detail::str_to_float_impl_exponent_1<FloatType>(
						sprout::next(str, 2),
						false,
						number,
						num_digits,
						num_decimals,
						exponent
						)
				: sprout::detail::str_to_float_impl_exponent_2<FloatType>(
					str,
					negative,
					number,
					num_digits,
					num_decimals,
					exponent
					)
				;
		}
		template<typename FloatType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR FloatType
		str_to_float_impl_decimal_1(
			NullTerminatedIterator const& str,
			bool negative,
			FloatType number = FloatType(),
			std::size_t num_digits = 0,
			std::size_t num_decimals = 0,
			long exponent = 0
			)
		{
			return num_digits == 0 ? FloatType()
				: sprout::detail::str_to_float_impl_exponent<FloatType>(
					str,
					negative,
					negative ? -number : number,
					num_digits,
					num_decimals,
					exponent
					)
				;
		}
		template<typename FloatType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR FloatType
		str_to_float_impl_decimal(
			NullTerminatedIterator const& str,
			bool negative,
			FloatType number = FloatType(),
			std::size_t num_digits = 0,
			std::size_t num_decimals = 0,
			long exponent = 0
			)
		{
			typedef typename std::iterator_traits<NullTerminatedIterator>::value_type char_type;
			SPROUT_STATIC_ASSERT(sprout::detail::is_char_type_of_consecutive_digits<char_type>::value);
			return sprout::ascii::isdigit(*str) ? sprout::detail::str_to_float_impl_decimal<FloatType>(
					sprout::next(str),
					negative,
					number * 10 + (*str - SPROUT_CHAR_LITERAL('0', char_type)),
					num_digits + 1,
					num_decimals + 1,
					exponent
					)
				: sprout::detail::str_to_float_impl_decimal_1<FloatType>(
					str,
					negative,
					number,
					num_digits,
					num_decimals,
					exponent - num_decimals
					)
				;
		}

		template<typename FloatType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR FloatType
		str_to_float_impl(
			NullTerminatedIterator const& str,
			bool negative,
			FloatType number = FloatType(),
			std::size_t num_digits = 0
			)
		{
			typedef typename std::iterator_traits<NullTerminatedIterator>::value_type char_type;
			SPROUT_STATIC_ASSERT(sprout::detail::is_char_type_of_consecutive_digits<char_type>::value);
			return sprout::ascii::isdigit(*str) ? sprout::detail::str_to_float_impl<FloatType>(
					sprout::next(str),
					negative,
					number * 10 + (*str - SPROUT_CHAR_LITERAL('0', char_type)),
					num_digits + 1
					)
				: *str == SPROUT_CHAR_LITERAL('.', char_type) ? sprout::detail::str_to_float_impl_decimal<FloatType>(
					sprout::next(str),
					negative,
					number,
					num_digits
					)
				: sprout::detail::str_to_float_impl_decimal_1<FloatType>(
					str,
					negative,
					number,
					num_digits
					)
				;
		}
		template<typename FloatType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR FloatType
		str_to_float(NullTerminatedIterator const& str) {
			typedef typename std::iterator_traits<NullTerminatedIterator>::value_type char_type;
			return sprout::ascii::isspace(*str)
				? sprout::detail::str_to_float<FloatType>(sprout::next(str))
				: *str == SPROUT_CHAR_LITERAL('-', char_type)
				? sprout::detail::str_to_float_impl<FloatType>(sprout::next(str), true)
				: *str == SPROUT_CHAR_LITERAL('+', char_type)
				? sprout::detail::str_to_float_impl<FloatType>(sprout::next(str), false)
				: sprout::detail::str_to_float_impl<FloatType>(str, false)
				;
		}
		template<typename FloatType, typename NullTerminatedIterator, typename CharPtr>
		inline SPROUT_CONSTEXPR FloatType
		str_to_float(NullTerminatedIterator const& str, CharPtr* endptr) {
			return !endptr ? sprout::detail::str_to_float<FloatType>(str)
#if defined(__MINGW32__)
				: std::is_same<typename std::remove_cv<FloatType>::type, float>::value ? ::strtof(&*str, endptr)
				: std::is_same<typename std::remove_cv<FloatType>::type, double>::value ? std::strtod(&*str, endptr)
				: ::strtold(&*str, endptr)
#else
				: std::is_same<typename std::remove_cv<FloatType>::type, float>::value ? std::strtof(&*str, endptr)
				: std::is_same<typename std::remove_cv<FloatType>::type, double>::value ? std::strtod(&*str, endptr)
				: std::strtold(&*str, endptr)
#endif
				;
		}
	}	// namespace detail

	//
	// str_to_float
	//
	template<typename FloatType, typename Char>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_floating_point<FloatType>::value,
		FloatType
	>::type
	str_to_float(Char const* str, Char** endptr) {
		return sprout::detail::str_to_float<FloatType>(str, endptr);
	}

	template<typename FloatType, typename Char>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_floating_point<FloatType>::value,
		FloatType
	>::type
	str_to_float(Char const* str, std::nullptr_t) {
		return sprout::detail::str_to_float<FloatType>(str);
	}

	template<typename FloatType, typename Char>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_floating_point<FloatType>::value,
		FloatType
	>::type
	str_to_float(Char const* str) {
		return sprout::detail::str_to_float<FloatType>(str);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STR_TO_FLOAT_HPP
