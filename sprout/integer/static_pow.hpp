/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INTEGER_STATIC_POW_HPP
#define SPROUT_INTEGER_STATIC_POW_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// static_pow2
	//
	template<typename T, T X>
	struct static_pow2
		: public sprout::integral_constant<T, (1 << X)>
	{};

	namespace detail {
		template<typename T, T X, bool IsZero = (X == 0)>
		struct static_pow2m1;
		template<typename T, T X>
		struct static_pow2m1<T, X, true>
			: public sprout::integral_constant<T, 1>
		{};
		template<typename T, T X>
		struct static_pow2m1<T, X, false>
			: public sprout::integral_constant<T, ((((T(1) << (X - 1)) - 1) << 1) + 1)>
		{};
	}	// namespace detail
	//
	// static_pow2m1
	//
	template<typename T, T X>
	struct static_pow2m1
		: public sprout::detail::static_pow2m1<T, X>
	{};

	namespace detail {
		template<typename T, T X, T Y, int K = (Y < 3 ? int(Y) : 3), bool IsOdd = (Y % 2 != 0)>
		struct static_pow;
		template<typename T, T X, T Y>
		struct static_pow<T, X, Y, 0, false>
			: public sprout::integral_constant<T, 1>
		{};
		template<typename T, T X, T Y>
		struct static_pow<T, X, Y, 1, true>
			: public sprout::integral_constant<T, X>
		{};
		template<typename T, T X, T Y>
		struct static_pow<T, X, Y, 2, false>
			: public sprout::integral_constant<T, X * X>
		{};
		template<typename T, T X, T Y, int K>
		struct static_pow<T, X, Y, K, false>
			: public sprout::detail::static_pow<T, sprout::detail::static_pow<T, X, Y / 2>::value, 2>
		{};
		template<typename T, T X, T Y, int K>
		struct static_pow<T, X, Y, K, true>
			: public sprout::integral_constant<T, X * sprout::detail::static_pow<T, X, Y - 1>::value>
		{};
	}	// namespace detail
	//
	// static_pow
	//
	template<typename T, T X, T Y>
	struct static_pow
		: public sprout::detail::static_pow<T, X, Y>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INTEGER_STATIC_POW_HPP
