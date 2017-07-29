/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDLIB_STR_TO_INT_HPP
#define SPROUT_CSTDLIB_STR_TO_INT_HPP

#include <cstdlib>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/type_traits/is_signed.hpp>
#include <sprout/type_traits/is_unsigned.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/ctype/ascii.hpp>
#include <sprout/detail/char_literal.hpp>
#include <sprout/detail/char_conversion.hpp>
#if !defined(_MSC_VER)
#	include <cinttypes>
#endif

namespace sprout {
	namespace detail {
		// Copyright (c) 2011 osyo-manga : http://d.hatena.ne.jp/osyo-manga/

		template<typename IntType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR IntType
		str_to_int_impl_1(NullTerminatedIterator const& str, int base, IntType val, IntType x, bool negative) {
			return x == static_cast<IntType>(-1) ? (negative ? -1 * val : val)
				: val > (sprout::numeric_limits<IntType>::max() - x - (negative ? 1 : 0)) / base
					? (negative ? sprout::numeric_limits<IntType>::min() : sprout::numeric_limits<IntType>::max())
				: sprout::detail::str_to_int_impl_1<IntType>(
					sprout::next(str),
					base,
					val * base + x,
					sprout::detail::char_to_int<IntType>(*sprout::next(str), base),
					negative
					)
				;
		}
		template<typename IntType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR IntType
		str_to_int_impl(NullTerminatedIterator const& str, int base, bool negative) {
			typedef typename std::iterator_traits<NullTerminatedIterator>::value_type char_type;
			return *str == SPROUT_CHAR_LITERAL('0', char_type)
				? *sprout::next(str) == SPROUT_CHAR_LITERAL('x', char_type)
					|| *sprout::next(str) == SPROUT_CHAR_LITERAL('X', char_type)
					? sprout::detail::str_to_int_impl_1<IntType>(
						sprout::next(str, 2),
						base ? base : 16,
						IntType(),
						sprout::detail::char_to_int<IntType>(*sprout::next(str, 2), base ? base : 16),
						negative
						)
					: sprout::detail::str_to_int_impl_1<IntType>(
						sprout::next(str),
						base ? base : 8,
						IntType(),
						sprout::detail::char_to_int<IntType>(*sprout::next(str), base ? base : 8),
						negative
						)
				: sprout::detail::str_to_int_impl_1<IntType>(
					str,
					base ? base : 10,
					IntType(),
					sprout::detail::char_to_int<IntType>(*str, base ? base : 10),
					negative
					)
				;
		}
		template<typename IntType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_unsigned<IntType>::value,
			IntType
		>::type
		str_to_int(NullTerminatedIterator const& str, int base) {
			typedef typename std::iterator_traits<NullTerminatedIterator>::value_type char_type;
			return sprout::ascii::isspace(*str)
					? sprout::detail::str_to_int<IntType>(sprout::next(str), base)
				: *str == SPROUT_CHAR_LITERAL('+', char_type)
					? sprout::detail::str_to_int_impl<IntType>(sprout::next(str), base, false)
				: sprout::detail::str_to_int_impl<IntType>(str, base, false)
				;
		}
		template<typename IntType, typename NullTerminatedIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_signed<IntType>::value,
			IntType
		>::type
		str_to_int(NullTerminatedIterator const& str, int base) {
			typedef typename std::iterator_traits<NullTerminatedIterator>::value_type char_type;
			return sprout::ascii::isspace(*str)
					? sprout::detail::str_to_int<IntType>(sprout::next(str), base)
				: *str == SPROUT_CHAR_LITERAL('-', char_type)
					? sprout::detail::str_to_int_impl<IntType>(sprout::next(str), base, true)
				: *str == SPROUT_CHAR_LITERAL('+', char_type)
					? sprout::detail::str_to_int_impl<IntType>(sprout::next(str), base, false)
				: sprout::detail::str_to_int_impl<IntType>(str, base, false)
				;
		}
		template<typename IntType, typename NullTerminatedIterator, typename CharPtr>
		inline SPROUT_CONSTEXPR IntType
		str_to_int(NullTerminatedIterator const& str, CharPtr* endptr, int base) {
			return !endptr ? sprout::detail::str_to_int<IntType>(str, base)
#if defined(_MSC_VER)
				: sprout::is_signed<IntType>::value
					? static_cast<IntType>(std::strtol(&*str, endptr, base))
					: static_cast<IntType>(std::strtoul(&*str, endptr, base))
#elif defined(__MINGW32__)
				: sprout::is_signed<IntType>::value
					? sizeof(IntType) <= sizeof(long) ? static_cast<IntType>(std::strtol(&*str, endptr, base))
						: sizeof(IntType) <= sizeof(long long) ? static_cast<IntType>(::strtoll(&*str, endptr, base))
						: static_cast<IntType>(std::strtoimax(&*str, endptr, base))
					: sizeof(IntType) <= sizeof(unsigned long) ? static_cast<IntType>(std::strtoul(&*str, endptr, base))
						: sizeof(IntType) <= sizeof(unsigned long long) ? static_cast<IntType>(::strtoull(&*str, endptr, base))
						: static_cast<IntType>(std::strtoumax(&*str, endptr, base))
#else
				: sprout::is_signed<IntType>::value
					? sizeof(IntType) <= sizeof(long) ? static_cast<IntType>(std::strtol(&*str, endptr, base))
						: sizeof(IntType) <= sizeof(long long) ? static_cast<IntType>(std::strtoll(&*str, endptr, base))
						: static_cast<IntType>(std::strtoimax(&*str, endptr, base))
					: sizeof(IntType) <= sizeof(unsigned long) ? static_cast<IntType>(std::strtoul(&*str, endptr, base))
						: sizeof(IntType) <= sizeof(unsigned long long) ? static_cast<IntType>(std::strtoull(&*str, endptr, base))
						: static_cast<IntType>(std::strtoumax(&*str, endptr, base))
#endif
				;
		}
	}	// namespace detail

	//
	// str_to_int
	//
	template<typename IntType, typename Char>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<IntType>::value,
		IntType
	>::type
	str_to_int(Char const* str, Char** endptr, int base = 10) {
		return sprout::detail::str_to_int<IntType>(str, endptr, base);
	}

	template<typename IntType, typename Char>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<IntType>::value,
		IntType
	>::type
	str_to_int(Char const* str, std::nullptr_t, int base = 10) {
		return sprout::detail::str_to_int<IntType>(str, base);
	}

	template<typename IntType, typename Char>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_integral<IntType>::value,
		IntType
	>::type
	str_to_int(Char const* str, int base = 10) {
		return sprout::detail::str_to_int<IntType>(str, base);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STR_TO_INT_HPP
