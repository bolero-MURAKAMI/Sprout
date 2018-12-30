/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_EXPONENTIAL_HPP
#define SPROUT_VALARRAY_EXPONENTIAL_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/valarray/valarray.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/math/exp10.hpp>
#include <sprout/math/exp2.hpp>
#include <sprout/math/expm1.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/log10.hpp>
#include <sprout/math/log1p.hpp>
#include <sprout/math/log2.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout_math_detail {
	using sprout::math::exp;
	using sprout::math::exp10;
	using sprout::math::exp2;
	using sprout::math::expm1;
	using sprout::math::log;
	using sprout::math::log10;
	using sprout::math::log1p;
	using sprout::math::log2;

	template<typename T>
	inline SPROUT_CONSTEXPR decltype(exp(std::declval<T>()))
	call_exp(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(exp(std::declval<T>()))
	{
		return exp(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(exp10(std::declval<T>()))
	call_exp10(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(exp10(std::declval<T>()))
	{
		return exp10(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(exp2(std::declval<T>()))
	call_exp2(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(exp2(std::declval<T>()))
	{
		return exp2(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(expm1(std::declval<T>()))
	call_expm1(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(expm1(std::declval<T>()))
	{
		return expm1(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(log(std::declval<T>()))
	call_log(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(log(std::declval<T>()))
	{
		return log(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(log10(std::declval<T>()))
	call_log10(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(log10(std::declval<T>()))
	{
		return log10(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(log1p(std::declval<T>()))
	call_log1p(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(log1p(std::declval<T>()))
	{
		return log1p(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(log2(std::declval<T>()))
	call_log2(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(log2(std::declval<T>()))
	{
		return log2(SPROUT_FORWARD(T, x));
	}
}	// namespace sprout

namespace sprout {
	namespace detail {
		struct exp_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_exp(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_exp(std::declval<T>()))
			{
				return sprout_math_detail::call_exp(SPROUT_FORWARD(T, x));
			}
		};
		struct exp10_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_exp10(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_exp10(std::declval<T>()))
			{
				return sprout_math_detail::call_exp10(SPROUT_FORWARD(T, x));
			}
		};
		struct exp2_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_exp2(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_exp2(std::declval<T>()))
			{
				return sprout_math_detail::call_exp2(SPROUT_FORWARD(T, x));
			}
		};
		struct expm1_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_expm1(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_expm1(std::declval<T>()))
			{
				return sprout_math_detail::call_expm1(SPROUT_FORWARD(T, x));
			}
		};
		struct log_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_log(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_log(std::declval<T>()))
			{
				return sprout_math_detail::call_log(SPROUT_FORWARD(T, x));
			}
		};
		struct log10_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_log10(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_log10(std::declval<T>()))
			{
				return sprout_math_detail::call_log10(SPROUT_FORWARD(T, x));
			}
		};
		struct log1p_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_log1p(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_log1p(std::declval<T>()))
			{
				return sprout_math_detail::call_log1p(SPROUT_FORWARD(T, x));
			}
		};
		struct log2_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_log2(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_log2(std::declval<T>()))
			{
				return sprout_math_detail::call_log2(SPROUT_FORWARD(T, x));
			}
		};
	}	// namespace detail

	//
	// exp
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	exp(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::exp_f());
	}
	//
	// exp10
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	exp10(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::exp10_f());
	}
	//
	// exp2
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	exp2(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::exp2_f());
	}
	//
	// expm1
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	expm1(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::expm1_f());
	}
	//
	// log
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	log(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::log_f());
	}
	//
	// log10
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	log10(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::log10_f());
	}
	//
	// log1p
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	log1p(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::log1p_f());
	}
	//
	// log2
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	log2(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::log2_f());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_EXPONENTIAL_HPP
