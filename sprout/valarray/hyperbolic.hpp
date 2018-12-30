/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_HYPERBOLIC_HPP
#define SPROUT_VALARRAY_HYPERBOLIC_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/valarray/valarray.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/math/acosh.hpp>
#include <sprout/math/asinh.hpp>
#include <sprout/math/atanh.hpp>
#include <sprout/math/cosh.hpp>
#include <sprout/math/sinh.hpp>
#include <sprout/math/tanh.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout_math_detail {
	using sprout::math::acosh;
	using sprout::math::asinh;
	using sprout::math::atanh;
	using sprout::math::cosh;
	using sprout::math::sinh;
	using sprout::math::tanh;

	template<typename T>
	inline SPROUT_CONSTEXPR decltype(acosh(std::declval<T>()))
	call_acosh(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(acosh(std::declval<T>()))
	{
		return acosh(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(asinh(std::declval<T>()))
	call_asinh(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(asinh(std::declval<T>()))
	{
		return asinh(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(atanh(std::declval<T>()))
	call_atanh(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(atanh(std::declval<T>()))
	{
		return atanh(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(cosh(std::declval<T>()))
	call_cosh(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(cosh(std::declval<T>()))
	{
		return cosh(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(sinh(std::declval<T>()))
	call_sinh(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(sinh(std::declval<T>()))
	{
		return sinh(SPROUT_FORWARD(T, x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR decltype(tanh(std::declval<T>()))
	call_tanh(T&& x)
	SPROUT_NOEXCEPT_IF_EXPR(tanh(std::declval<T>()))
	{
		return tanh(SPROUT_FORWARD(T, x));
	}
}	// namespace sprout

namespace sprout {
	namespace detail {
		struct acosh_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_acosh(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_acosh(std::declval<T>()))
			{
				return sprout_math_detail::call_acosh(SPROUT_FORWARD(T, x));
			}
		};
		struct asinh_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_asinh(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_asinh(std::declval<T>()))
			{
				return sprout_math_detail::call_asinh(SPROUT_FORWARD(T, x));
			}
		};
		struct atanh_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_atanh(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_atanh(std::declval<T>()))
			{
				return sprout_math_detail::call_atanh(SPROUT_FORWARD(T, x));
			}
		};
		struct cosh_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_cosh(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_cosh(std::declval<T>()))
			{
				return sprout_math_detail::call_cosh(SPROUT_FORWARD(T, x));
			}
		};
		struct sinh_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_sinh(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_sinh(std::declval<T>()))
			{
				return sprout_math_detail::call_sinh(SPROUT_FORWARD(T, x));
			}
		};
		struct tanh_f
			: public sprout::transparent<>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR decltype(sprout_math_detail::call_tanh(std::declval<T>()))
			operator()(T&& x)
			SPROUT_NOEXCEPT_IF_EXPR(sprout_math_detail::call_tanh(std::declval<T>()))
			{
				return sprout_math_detail::call_tanh(SPROUT_FORWARD(T, x));
			}
		};
	}	// namespace detail

	//
	// acosh
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	acosh(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::acosh_f());
	}
	//
	// asinh
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	asinh(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::asinh_f());
	}
	//
	// atanh
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	atanh(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::atanh_f());
	}
	//
	// cosh
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	cosh(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::cosh_f());
	}
	//
	// sinh
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	sinh(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::sinh_f());
	}
	//
	// tanh
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	tanh(sprout::valarray<T, N> const& x) {
		return sprout::fixed::transform(x.begin(), x.end(), x, sprout::detail::tanh_f());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_HYPERBOLIC_HPP
