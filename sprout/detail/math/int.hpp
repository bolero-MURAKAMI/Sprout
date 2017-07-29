/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_INT_HPP
#define SPROUT_DETAIL_INT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/is_sint.hpp>
#include <sprout/type_traits/is_uint.hpp>

namespace sprout {
	namespace detail {
		//
		// int_digits_mf
		//
		template<typename IntType, IntType Val, int Base = 10, bool = Val != 0>
		struct int_digits_mf_impl;
		template<typename IntType, IntType Val, int Base>
		struct int_digits_mf_impl<IntType, Val, Base, false>
			: public sprout::integral_constant<IntType, 0>
		{};
		template<typename IntType, IntType Val, int Base>
		struct int_digits_mf_impl<IntType, Val, Base, true>
			: public sprout::integral_constant<IntType, 1 + sprout::detail::int_digits_mf_impl<IntType, Val / Base, Base>::value>
		{};
		template<typename IntType, IntType Val, int Base = 10, bool = Val != 0>
		struct int_digits_mf;
		template<typename IntType, IntType Val, int Base>
		struct int_digits_mf<IntType, Val, Base, false>
			: public sprout::integral_constant<IntType, 1>
		{};
		template<typename IntType, IntType Val, int Base>
		struct int_digits_mf<IntType, Val, Base, true>
			: public sprout::integral_constant<IntType, 1 + sprout::detail::int_digits_mf_impl<IntType, Val / Base, Base>::value>
		{};

		//
		// int_pow
		//
		template<
			typename IntType, int Base = 10,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR IntType
		int_pow(int exponent) {
			return exponent ? Base * sprout::detail::int_pow<IntType, Base>(exponent - 1)
				: 1
				;
		}

		//
		// int_digits
		//
		template<int Base = 10, typename IntType>
		inline SPROUT_CONSTEXPR int
		int_digits_impl(IntType val) {
			return val ? 1 + sprout::detail::int_digits_impl<Base>(val / Base)
				: 0
				;
		}
		template<
			int Base = 10, typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		int_digits(IntType val) {
			return val ? 1 + sprout::detail::int_digits_impl<Base>(val / Base)
				: 1
				;
		}

		//
		// int_digit_at
		//
		template<
			int Base = 10, typename IntType,
			typename sprout::enabler_if<sprout::is_sint<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		int_digit_at(IntType val, int digits) {
			return val < 0 ? -((val / sprout::detail::int_pow<IntType, Base>(digits)) % Base)
				: (val / sprout::detail::int_pow<IntType, Base>(digits)) % Base
				;
		}
		template<
			int Base = 10, typename IntType,
			typename sprout::enabler_if<sprout::is_uint<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		int_digit_at(IntType val, int digits) {
			return (val / sprout::detail::int_pow<IntType, Base>(digits)) % Base;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_INT_HPP
