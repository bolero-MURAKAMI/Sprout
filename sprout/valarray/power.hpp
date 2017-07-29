/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_POWER_HPP
#define SPROUT_VALARRAY_POWER_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/valarray/valarray.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/math/cbrt.hpp>
#include <sprout/math/abs.hpp>
#include <sprout/math/hypot.hpp>
#include <sprout/math/pow.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/math/log_a.hpp>
#include <sprout/cstdlib/abs.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout_math_detail {
	using sprout::math::cbrt;
	using sprout::math::abs;
	using sprout::math::hypot;
	using sprout::math::pow;
	using sprout::math::sqrt;
	using sprout::math::log_a;
	using sprout::abs;

	template<typename T>
	inline SPROUT_CONSTEXPR decltype(cbrt(std::declval<T>()))
	call_cbrt(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(cbrt(std::declval<T>()))
	{
		return cbrt(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(abs(std::declval<T>()))
	call_abs(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(abs(std::declval<T>()))
	{
		return abs(SPROUT_FORWARD(T, x));
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR decltype(hypot(std::declval<T>(), std::declval<U>()))
	call_hypot(T&& x, U&& y)
	SPROUT_NOEXCEPT_IF_EXPR(hypot(std::declval<T>(), std::declval<U>()))
	{
		return hypot(SPROUT_FORWARD(T, x), SPROUT_FORWARD(U, y));
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR decltype(pow(std::declval<T>(), std::declval<U>()))
	call_pow(T&& x, U&& y)
	SPROUT_NOEXCEPT_IF_EXPR(pow(std::declval<T>(), std::declval<U>()))
	{
		return pow(SPROUT_FORWARD(T, x), SPROUT_FORWARD(U, y));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(sqrt(std::declval<T>()))
	call_sqrt(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(sqrt(std::declval<T>()))
	{
		return sqrt(SPROUT_FORWARD(T, x));
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR decltype(log_a(std::declval<T>(), std::declval<U>()))
	call_log_a(T&& x, U&& y)
	SPROUT_NOEXCEPT_IF_EXPR(log_a(std::declval<T>(), std::declval<U>()))
	{
		return log_a(SPROUT_FORWARD(T, x), SPROUT_FORWARD(U, y));
	}
}	// namespace sprout

namespace sprout {
	namespace detail {
		struct cbrt_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_cbrt(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_cbrt(std::declval<T>()))
			{
				return sprout_math_detail::call_cbrt(SPROUT_FORWARD(T, x));
			}
		};
		struct abs_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_abs(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_abs(std::declval<T>()))
			{
				return sprout_math_detail::call_abs(SPROUT_FORWARD(T, x));
			}
		};
		struct hypot_f
			: public sprout::transparent<>
		{
		public:
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_hypot(std::declval<T>(), std::declval<U>()))
			operator()(T&& x, U&& y)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_hypot(std::declval<T>(), std::declval<U>()))
			{
				return sprout_math_detail::call_hypot(SPROUT_FORWARD(T, x), SPROUT_FORWARD(U, y));
			}
		};
		struct pow_f
			: public sprout::transparent<>
		{
		public:
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_pow(std::declval<T>(), std::declval<U>()))
			operator()(T&& x, U&& y)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_pow(std::declval<T>(), std::declval<U>()))
			{
				return sprout_math_detail::call_pow(SPROUT_FORWARD(T, x), SPROUT_FORWARD(U, y));
			}
		};
		struct sqrt_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_sqrt(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_sqrt(std::declval<T>()))
			{
				return sprout_math_detail::call_sqrt(SPROUT_FORWARD(T, x));
			}
		};
		struct log_a_f
			: public sprout::transparent<>
		{
		public:
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_log_a(std::declval<T>(), std::declval<U>()))
			operator()(T&& x, U&& y)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_log_a(std::declval<T>(), std::declval<U>()))
			{
				return sprout_math_detail::call_log_a(SPROUT_FORWARD(T, x), SPROUT_FORWARD(U, y));
			}
		};
	}	// namespace detail

	//
	// cbrt
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	cbrt(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::cbrt_f());
	}
	//
	// abs
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	abs(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::abs_f());
	}
	//
	// hypot
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	hypot(sprout::valarray<T, N> const& x, sprout::valarray<T, N> const& y) {
		return sprout::fixed::transform(x.begin(), x.end(), y.end(), x, sprout::detail::hypot_f());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	hypot(sprout::valarray<T, N> const& x, T const& y) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::bind2nd(sprout::detail::hypot_f(), y));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	hypot(T const& x, sprout::valarray<T, N> const& y) {
		return sprout::fixed::transform(y.begin(), y.end(), y, sprout::bind1st(sprout::detail::hypot_f(), x));
	}
	//
	// pow
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	pow(sprout::valarray<T, N> const& x, sprout::valarray<T, N> const& y) {
		return sprout::fixed::transform(x.begin(), x.end(), y.end(), x, sprout::detail::pow_f());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	pow(sprout::valarray<T, N> const& x, T const& y) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::bind2nd(sprout::detail::pow_f(), y));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	pow(T const& x, sprout::valarray<T, N> const& y) {
		return sprout::fixed::transform(y.begin(), y.end(), y, sprout::bind1st(sprout::detail::pow_f(), x));
	}
	//
	// sqrt
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	sqrt(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::sqrt_f());
	}
	//
	// log_a
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	log_a(sprout::valarray<T, N> const& x, sprout::valarray<T, N> const& y) {
		return sprout::fixed::transform(x.begin(), x.end(), y.end(), x, sprout::detail::log_a_f());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	log_a(sprout::valarray<T, N> const& x, T const& y) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::bind2nd(sprout::detail::log_a_f(), y));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	log_a(T const& x, sprout::valarray<T, N> const& y) {
		return sprout::fixed::transform(y.begin(), y.end(), y, sprout::bind1st(sprout::detail::log_a_f(), x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_POWER_HPP
