#ifndef SPROUT_CSTDLIB_DECIMAL_TO_INT_HPP
#define SPROUT_CSTDLIB_DECIMAL_TO_INT_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/ctype/ascii.hpp>

namespace sprout {
	namespace detail {
		// Copyright (c) 2011 osyo-manga : http://d.hatena.ne.jp/osyo-manga/

		template<typename IntType, typename CStrIterator>
		inline SPROUT_CONSTEXPR IntType
		ascii_to_int_impl(CStrIterator str, IntType val, bool negative) {
			return !sprout::ascii::isdigit(*str)
				? negative ? -val : val
				: val > (sprout::numeric_limits<IntType>::max() - (*str - static_cast<typename std::iterator_traits<CStrIterator>::value_type>('0')) - (negative ? 1 : 0)) / 10
				? (negative ? sprout::numeric_limits<IntType>::min() : sprout::numeric_limits<IntType>::max())
				: sprout::detail::ascii_to_int_impl<IntType>(
					sprout::next(str),
					val * 10 + (*str - static_cast<typename std::iterator_traits<CStrIterator>::value_type>('0')),
					negative
					)
				;
		}
		template<typename IntType, typename CStrIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_unsigned<IntType>::value,
			IntType
		>::type
		ascii_to_int(CStrIterator str) {
			return sprout::ascii::isspace(*str)
				? sprout::detail::ascii_to_int<IntType>(sprout::next(str))
				: *str == static_cast<typename std::iterator_traits<CStrIterator>::value_type>('+')
				? sprout::detail::ascii_to_int_impl<IntType>(sprout::next(str), IntType(), false)
				: sprout::detail::ascii_to_int_impl<IntType>(str, IntType(), false)
				;
		}
		template<typename IntType, typename CStrIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_signed<IntType>::value,
			IntType
		>::type
		ascii_to_int(CStrIterator str) {
			return sprout::ascii::isspace(*str)
				? sprout::detail::ascii_to_int<IntType>(sprout::next(str))
				: *str == static_cast<typename std::iterator_traits<CStrIterator>::value_type>('-')
				? sprout::detail::ascii_to_int_impl<IntType>(sprout::next(str), IntType(), true)
				: *str == static_cast<typename std::iterator_traits<CStrIterator>::value_type>('+')
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
