/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_BITWISE_HPP
#define SPROUT_VALARRAY_BITWISE_HPP

#include <utility>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/valarray/valarray.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/math/acos.hpp>
#include <sprout/math/asin.hpp>
#include <sprout/math/atan.hpp>
#include <sprout/math/atan2.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/tan.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout_math_detail {
	using sprout::math::acos;
	using sprout::math::asin;
	using sprout::math::atan;
	using sprout::math::atan2;
	using sprout::math::cos;
	using sprout::math::sin;
	using sprout::math::tan;

	template<typename T>
	inline SPROUT_CONSTEXPR decltype(acos(std::declval<T>()))
	call_acos(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(acos(std::declval<T>()))
	{
		return acos(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(asin(std::declval<T>()))
	call_asin(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(asin(std::declval<T>()))
	{
		return asin(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(atan(std::declval<T>()))
	call_atan(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(atan(std::declval<T>()))
	{
		return atan(SPROUT_FORWARD(T, x));
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR decltype(atan2(std::declval<T>(), std::declval<U>()))
	call_atan2(T&& x, U&& y)
	SPROUT_NOEXCEPT_IF_EXPR(atan2(std::declval<T>(), std::declval<U>()))
	{
		return atan2(SPROUT_FORWARD(T, x), SPROUT_FORWARD(U, u));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(cos(std::declval<T>()))
	call_cos(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(cos(std::declval<T>()))
	{
		return cos(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(sin(std::declval<T>()))
	call_sin(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(sin(std::declval<T>()))
	{
		return sin(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(tan(std::declval<T>()))
	call_tan(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(tan(std::declval<T>()))
	{
		return tan(SPROUT_FORWARD(T, x));
	}
}	// namespace sprout

namespace sprout {
	namespace detail {
		struct acos_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_acos(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_acos(std::declval<T>()))
			{
				return sprout_math_detail::call_acos(SPROUT_FORWARD(T, x));
			}
		};
		struct asin_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_asin(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_asin(std::declval<T>()))
			{
				return sprout_math_detail::call_asin(SPROUT_FORWARD(T, x));
			}
		};
		struct atan_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_atan(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_atan(std::declval<T>()))
			{
				return sprout_math_detail::call_atan(SPROUT_FORWARD(T, x));
			}
		};
		struct atan2_f
			: public sprout::transparent<>
		{
		public:
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_atan2(std::declval<T>(), std::declval<U>()))
			operator()(T&& x, U&& y)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_atan2(std::declval<T>(), std::declval<U>()))
			{
				return sprout_math_detail::call_atan2(SPROUT_FORWARD(T, x), SPROUT_FORWARD(U, y));
			}
		};
		struct cos_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_cos(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_cos(std::declval<T>()))
			{
				return sprout_math_detail::call_cos(SPROUT_FORWARD(T, x));
			}
		};
		struct sin_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_sin(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_sin(std::declval<T>()))
			{
				return sprout_math_detail::call_sin(SPROUT_FORWARD(T, x));
			}
		};
		struct tan_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_tan(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_tan(std::declval<T>()))
			{
				return sprout_math_detail::call_tan(SPROUT_FORWARD(T, x));
			}
		};
	}	// namespace detail

	//
	// acos
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	acos(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::acos_f());
	}
	//
	// asin
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	asin(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::asin_f());
	}
	//
	// atan
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	atan(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::atan_f());
	}
	//
	// atan2
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	atan2(sprout::valarray<T, N> const& x, sprout::valarray<T, N> const& y) {
		return sprout::fixed::transform(x.begin(), x.end(), y.end(), x, sprout::detail::atan2_f());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	atan2(sprout::valarray<T, N> const& lhs, T const& y) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::bind2nd(sprout::detail::atan2_f()()), y));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	atan2(T const& x, sprout::valarray<T, N> const& y) {
		return sprout::fixed::transform(y.begin(), y.end(), y, sprout::bind1st(sprout::detail::atan2_f()()), x));
	}
	//
	// cos
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	cos(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::cos_f());
	}
	//
	// sin
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	sin(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::sin_f());
	}
	//
	// tan
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	tan(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::tan_f());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_BITWISE_HPP
