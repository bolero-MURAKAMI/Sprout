/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INTEGER_INTEGER_DIGITS_HPP
#define SPROUT_INTEGER_INTEGER_DIGITS_HPP

#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace detail {
		template<typename IntType, long N, long D>
		struct integer_digits_impl
			: public sprout::integral_constant<
				std::size_t,
				(CHAR_BIT * sizeof(IntType) - (std::is_signed<IntType>::value ? 1 : 0)) * N / D
				+ ((CHAR_BIT * sizeof(IntType) - (std::is_signed<IntType>::value ? 1 : 0)) * N % D ? 1 : 0)
			>
		{};
	}	// namespace detail

	//
	// integer_digits
	//
	template<typename IntType, std::size_t Base = 10>
	struct integer_digits;

	template<typename IntType>
	struct integer_digits<IntType, 2>
		: public sprout::detail::integer_digits_impl<IntType, 1, 1>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 3>
		: public sprout::detail::integer_digits_impl<IntType, 630, 1000>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 4>
		: public sprout::detail::integer_digits_impl<IntType, 1, 2>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 5>
		: public sprout::detail::integer_digits_impl<IntType, 430, 1000>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 6>
		: public sprout::detail::integer_digits_impl<IntType, 386, 1000>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 7>
		: public sprout::detail::integer_digits_impl<IntType, 356, 1000>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 8>
		: public sprout::detail::integer_digits_impl<IntType, 1, 3>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 9>
		: public sprout::detail::integer_digits_impl<IntType, 315, 1000>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 10>
		: public sprout::detail::integer_digits_impl<IntType, 301, 1000>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 11>
		: public sprout::detail::integer_digits_impl<IntType, 289, 1000>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 12>
		: public sprout::detail::integer_digits_impl<IntType, 278, 1000>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 13>
		: public sprout::detail::integer_digits_impl<IntType, 270, 1000>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 14>
		: public sprout::detail::integer_digits_impl<IntType, 262, 1000>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 15>
		: public sprout::detail::integer_digits_impl<IntType, 255, 1000>
	{};
	template<typename IntType>
	struct integer_digits<IntType, 16>
		: public sprout::detail::integer_digits_impl<IntType, 1, 4>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INTEGER_INTEGER_DIGITS_HPP
