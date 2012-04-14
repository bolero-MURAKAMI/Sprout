#ifndef SPROUT_CSTDLIB_STR_TO_INT_HPP
#define SPROUT_CSTDLIB_STR_TO_INT_HPP

#include <cstddef>
#include <cstdlib>
#include <limits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/enabler_if.hpp>
#include <sprout/detail/char_conversion.hpp>

namespace sprout {
	namespace detail {
		// Copyright (c) 2011 osyo-manga : http://d.hatena.ne.jp/osyo-manga/

		template<typename IntType, typename CStrIterator>
		inline SPROUT_CONSTEXPR IntType str_to_int_impl_1(CStrIterator str, int base, IntType val, IntType x, bool negative) {
			return x == static_cast<IntType>(-1)
				? (negative ? -val : val)
				: val > (std::numeric_limits<IntType>::max() - x - (negative ? 1 : 0)) / base
				? (negative ? std::numeric_limits<IntType>::min() : std::numeric_limits<IntType>::max())
				: sprout::detail::str_to_int_impl_1<IntType>(
					sprout::next(str),
					base,
					val * base + x,
					sprout::detail::char_to_int<IntType>(*sprout::next(str), base),
					negative
					)
				;
		}
		template<typename IntType, typename CStrIterator>
		inline SPROUT_CONSTEXPR IntType str_to_int_impl(CStrIterator str, int base, bool negative) {
			return *str == static_cast<typename std::iterator_traits<CStrIterator>::value_type>('0')
				? *sprout::next(str) == static_cast<typename std::iterator_traits<CStrIterator>::value_type>('x')
					|| *sprout::next(str) == static_cast<typename std::iterator_traits<CStrIterator>::value_type>('X')
					? sprout::detail::str_to_int_impl_1<IntType>(
						sprout::next(str, 2),
						base ? base : 16,
						IntType(),
						sprout::detail::char_to_int<IntType>(*sprout::next(str, 2), base),
						negative
						)
					: sprout::detail::str_to_int_impl_1<IntType>(
						sprout::next(str),
						base ? base : 8,
						IntType(),
						sprout::detail::char_to_int<IntType>(*sprout::next(str), base),
						negative
						)
				: sprout::detail::str_to_int_impl_1<IntType>(
					str,
					base ? base : 10,
					IntType(),
					sprout::detail::char_to_int<IntType>(*str, base),
					negative
					)
				;
		}
		template<typename IntType, typename CStrIterator>
		inline SPROUT_CONSTEXPR IntType str_to_int(CStrIterator str, int base) {
			return sprout::ascii::isspace(*str)
				? sprout::detail::str_to_int<IntType>(sprout::next(str), base)
				: *str == static_cast<typename std::iterator_traits<CStrIterator>::value_type>('-')
				? sprout::detail::str_to_int_impl<IntType>(sprout::next(str), base, true)
				: *str == static_cast<typename std::iterator_traits<CStrIterator>::value_type>('+')
				? sprout::detail::str_to_int_impl<IntType>(sprout::next(str), base, false)
				: sprout::detail::str_to_int_impl<IntType>(str, base, false)
				;
		}
		template<typename IntType, typename CStrIterator, typename CharPtr>
		inline SPROUT_CONSTEXPR IntType str_to_int(CStrIterator str, CharPtr* endptr, int base) {
			return !endptr ? sprout::detail::str_to_int<IntType>(str, base)
				: std::strtol(str, endptr, base)
				;
		}
	}	// namespace detail

	//
	// str_to_int
	//
	template<typename IntType, typename Char, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR IntType str_to_int(Char const* str, Char** endptr, int base = 10) {
		return sprout::detail::str_to_int<IntType>(str, endptr, base);
	}
	template<typename IntType, typename Char, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR IntType str_to_int(Char const* str, std::nullptr_t endptr, int base = 10) {
		return sprout::detail::str_to_int<IntType>(str, base);
	}
	template<typename IntType, typename Char, typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR IntType str_to_int(Char const* str, int base = 10) {
		return sprout::detail::str_to_int<IntType>(str, base);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_STR_TO_INT_HPP
