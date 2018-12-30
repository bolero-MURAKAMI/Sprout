/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIMITS_HPP
#define SPROUT_LIMITS_HPP

#include <limits>
#include <sprout/config.hpp>
#ifdef SPROUT_NO_CXX11_NUMERIC_LIMITS
#	include <cstdint>
#	include <climits>
#	include <cfloat>
#	if !defined(__FLT_DENORM_MIN__) || !defined(__LDBL_DENORM_MIN__) || !defined(__LDBL_DENORM_MIN__)
#		include <cmath>
#	endif	// #if !defined(__FLT_DENORM_MIN__) || !defined(__LDBL_DENORM_MIN__) || !defined(__LDBL_DENORM_MIN__)
#endif	// #ifdef SPROUT_NO_CXX11_NUMERIC_LIMITS

namespace sprout {
	//
	// numeric_limits
	//
#ifdef SPROUT_NO_CXX11_NUMERIC_LIMITS
	namespace detail {
		template<typename T>
		class numeric_limits_base {
		private:
			typedef std::numeric_limits<T> impl_type;
		public:
			SPROUT_STATIC_CONSTEXPR bool is_specialized = impl_type::is_specialized;

			SPROUT_STATIC_CONSTEXPR int digits = impl_type::digits;
			SPROUT_STATIC_CONSTEXPR int digits10 = impl_type::digits10;
			SPROUT_STATIC_CONSTEXPR int max_digits10 = impl_type::max_digits10;
			SPROUT_STATIC_CONSTEXPR bool is_signed = impl_type::is_signed;
			SPROUT_STATIC_CONSTEXPR bool is_integer = impl_type::is_integer;
			SPROUT_STATIC_CONSTEXPR bool is_exact = impl_type::is_exact;
			SPROUT_STATIC_CONSTEXPR int radix = impl_type::radix;

			SPROUT_STATIC_CONSTEXPR int min_exponent = impl_type::min_exponent;
			SPROUT_STATIC_CONSTEXPR int min_exponent10 = impl_type::min_exponent10;
			SPROUT_STATIC_CONSTEXPR int max_exponent = impl_type::max_exponent;
			SPROUT_STATIC_CONSTEXPR int max_exponent10 = impl_type::max_exponent10;
			SPROUT_STATIC_CONSTEXPR bool has_infinity = impl_type::has_infinity;
			SPROUT_STATIC_CONSTEXPR bool has_quiet_NaN = impl_type::has_quiet_NaN;
			SPROUT_STATIC_CONSTEXPR bool has_signaling_NaN = impl_type::has_signaling_NaN;
			SPROUT_STATIC_CONSTEXPR std::float_denorm_style has_denorm = impl_type::has_denorm;
			SPROUT_STATIC_CONSTEXPR bool has_denorm_loss = impl_type::has_denorm_loss;

			SPROUT_STATIC_CONSTEXPR bool is_iec559 = impl_type::is_iec559;
			SPROUT_STATIC_CONSTEXPR bool is_bounded = impl_type::is_bounded;
			SPROUT_STATIC_CONSTEXPR bool is_modulo = impl_type::is_modulo;
			SPROUT_STATIC_CONSTEXPR bool traps = impl_type::traps;
			SPROUT_STATIC_CONSTEXPR bool tinyness_before = impl_type::tinyness_before;
			SPROUT_STATIC_CONSTEXPR std::float_round_style round_style = impl_type::round_style;
		};

		template<typename T, bool IsInitialized>
		class numeric_limits_impl;
		template<typename T>
		class numeric_limits_impl<T, true>
			: public sprout::detail::numeric_limits_base<T>
		{
		private:
			typedef std::numeric_limits<T> impl_type;
		public:
			static SPROUT_CONSTEXPR T min() SPROUT_NOEXCEPT {
				return impl_type::min();
			}
			static SPROUT_CONSTEXPR T max() SPROUT_NOEXCEPT {
				return impl_type::max();
			}
			static SPROUT_CONSTEXPR T lowest() SPROUT_NOEXCEPT {
				return impl_type::lowest();
			}

			static SPROUT_CONSTEXPR T epsilon() SPROUT_NOEXCEPT {
				return impl_type::epsilon();
			}
			static SPROUT_CONSTEXPR T round_error() SPROUT_NOEXCEPT {
				return impl_type::round_error();
			}

			static SPROUT_CONSTEXPR T infinity() SPROUT_NOEXCEPT {
				return impl_type::infinity();
			}
			static SPROUT_CONSTEXPR T quiet_NaN() SPROUT_NOEXCEPT {
				return impl_type::quiet_NaN();
			}
			static SPROUT_CONSTEXPR T signaling_NaN() SPROUT_NOEXCEPT {
				return impl_type::signaling_NaN();
			}
			static SPROUT_CONSTEXPR T denorm_min() SPROUT_NOEXCEPT {
				return impl_type::denorm_min();
			}
		};
		template<typename T>
		class numeric_limits_impl<T, false>
			: public sprout::detail::numeric_limits_base<T>
		{
		public:
			static SPROUT_CONSTEXPR T min() SPROUT_NOEXCEPT {
				return T();
			}
			static SPROUT_CONSTEXPR T max() SPROUT_NOEXCEPT {
				return T();
			}
			static SPROUT_CONSTEXPR T lowest() SPROUT_NOEXCEPT {
				return T();
			}

			static SPROUT_CONSTEXPR T epsilon() SPROUT_NOEXCEPT {
				return T();
			}
			static SPROUT_CONSTEXPR T round_error() SPROUT_NOEXCEPT {
				return T();
			}

			static SPROUT_CONSTEXPR T infinity() SPROUT_NOEXCEPT {
				return T();
			}
			static SPROUT_CONSTEXPR T quiet_NaN() SPROUT_NOEXCEPT {
				return T();
			}
			static SPROUT_CONSTEXPR T signaling_NaN() SPROUT_NOEXCEPT {
				return T();
			}
			static SPROUT_CONSTEXPR T denorm_min() SPROUT_NOEXCEPT {
				return T();
			}
		};
	}	// namespace detail

	template<typename T>
	class numeric_limits
		: public sprout::detail::numeric_limits_impl<T, std::numeric_limits<T>::is_specialized>
	{};
	template<typename T>
	class numeric_limits<T const>
		: public sprout::numeric_limits<T>
	{};
	template<typename T>
	class numeric_limits<T volatile>
		: public sprout::numeric_limits<T>
	{};
	template<typename T>
	class numeric_limits<T const volatile>
		: public sprout::numeric_limits<T>
	{};

#define SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(TYPE, MIN, MAX) \
	template<> \
	class numeric_limits<TYPE> \
		: public sprout::detail::numeric_limits_base<TYPE> \
	{ \
	public: \
		static SPROUT_CONSTEXPR TYPE min() SPROUT_NOEXCEPT { \
			return MIN; \
		} \
		static SPROUT_CONSTEXPR TYPE max() SPROUT_NOEXCEPT { \
			return MAX; \
		} \
		static SPROUT_CONSTEXPR TYPE lowest() SPROUT_NOEXCEPT { \
			return min(); \
		} \
		 \
		static SPROUT_CONSTEXPR TYPE epsilon() SPROUT_NOEXCEPT { \
			return static_cast<TYPE>(0); \
		} \
		static SPROUT_CONSTEXPR TYPE round_error() SPROUT_NOEXCEPT { \
			return static_cast<TYPE>(0); \
		} \
		 \
		static SPROUT_CONSTEXPR TYPE infinity() SPROUT_NOEXCEPT { \
			return static_cast<TYPE>(0); \
		} \
		static SPROUT_CONSTEXPR TYPE quiet_NaN() SPROUT_NOEXCEPT { \
			return static_cast<TYPE>(0); \
		} \
		static SPROUT_CONSTEXPR TYPE signaling_NaN() SPROUT_NOEXCEPT { \
			return static_cast<TYPE>(0); \
		} \
		static SPROUT_CONSTEXPR TYPE denorm_min() SPROUT_NOEXCEPT { \
			return static_cast<TYPE>(0); \
		} \
	}

	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(bool, false, true);

	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(short, SHRT_MIN, SHRT_MAX);
	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(int, INT_MIN, INT_MAX);
	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(long, LONG_MIN, LONG_MAX);
	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(long long, LLONG_MIN, LLONG_MAX);
	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(unsigned short, static_cast<unsigned short>(0), USHRT_MAX);
	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(unsigned int, static_cast<unsigned int>(0), UINT_MAX);
	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(unsigned long, static_cast<unsigned long>(0), ULONG_MAX);
	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(unsigned long long, static_cast<unsigned long long>(0), ULLONG_MAX);

	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(signed char, SCHAR_MIN, SCHAR_MAX);
	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(unsigned char, static_cast<unsigned char>(0), UCHAR_MAX);
#if SPROUT_USE_UNICODE_LITERALS
	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(
		char16_t,
		static_cast<char16_t>(sprout::numeric_limits<std::uint_least16_t>::min()),
		static_cast<char16_t>(sprout::numeric_limits<std::uint_least16_t>::max())
		);
	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(
		char32_t,
		static_cast<char16_t>(sprout::numeric_limits<std::uint_least32_t>::min()),
		static_cast<char16_t>(sprout::numeric_limits<std::uint_least32_t>::max())
		);
#endif
	SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL(wchar_t, WCHAR_MIN, WCHAR_MAX);
#undef SPROUT_NUMERIC_LIMITS_INTEGRAL_SPECIALIZED_DECL

#define SPROUT_NUMERIC_LIMITS_FLOATING_POINT_SPECIALIZED_DECL(TYPE, MIN, MAX, EPS, RND, INF, QNAN, SNAN, DMIN) \
	template<> \
	class numeric_limits<TYPE> \
		: public sprout::detail::numeric_limits_base<TYPE> \
	{ \
	public: \
		static SPROUT_CONSTEXPR TYPE min() SPROUT_NOEXCEPT { \
			return MIN; \
		} \
		static SPROUT_CONSTEXPR TYPE max() SPROUT_NOEXCEPT { \
			return MAX; \
		} \
		static SPROUT_CONSTEXPR TYPE lowest() SPROUT_NOEXCEPT { \
			return -max(); \
		} \
		 \
		static SPROUT_CONSTEXPR TYPE epsilon() SPROUT_NOEXCEPT { \
			return EPS; \
		} \
		static SPROUT_CONSTEXPR TYPE round_error() SPROUT_NOEXCEPT { \
			return RND; \
		} \
		 \
		static SPROUT_CONSTEXPR TYPE infinity() SPROUT_NOEXCEPT { \
			return INF; \
		} \
		static SPROUT_CONSTEXPR TYPE quiet_NaN() SPROUT_NOEXCEPT { \
			return QNAN; \
		} \
		static SPROUT_CONSTEXPR TYPE signaling_NaN() SPROUT_NOEXCEPT { \
			return SNAN; \
		} \
		static SPROUT_CONSTEXPR TYPE denorm_min() SPROUT_NOEXCEPT { \
			return DMIN; \
		} \
	}

#if !defined(__FLT_DENORM_MIN__)
	SPROUT_NUMERIC_LIMITS_FLOATING_POINT_SPECIALIZED_DECL(
		float,
		FLT_MIN, FLT_MAX,
		FLT_EPSILON, 0.5F,
		INFINITY, NAN, NAN, FLT_MIN
		);
#else	// #if !defined(__FLT_DENORM_MIN__)
	SPROUT_NUMERIC_LIMITS_FLOATING_POINT_SPECIALIZED_DECL(
		float,
		FLT_MIN, FLT_MAX,
		FLT_EPSILON, 0.5F,
		__builtin_huge_valf(), __builtin_nanf(""), __builtin_nansf(""), __FLT_DENORM_MIN__
		);
#endif	// #if !defined(__FLT_DENORM_MIN__)
#if !defined(__DBL_DENORM_MIN__)
	SPROUT_NUMERIC_LIMITS_FLOATING_POINT_SPECIALIZED_DECL(
		double,
		DBL_MIN, DBL_MAX,
		DBL_EPSILON, 0.5,
		INFINITY, NAN, NAN, DBL_MIN
		);
#else	// #if !defined(__DBL_DENORM_MIN__)
	SPROUT_NUMERIC_LIMITS_FLOATING_POINT_SPECIALIZED_DECL(
		double,
		DBL_MIN, DBL_MAX,
		DBL_EPSILON, 0.5,
		__builtin_huge_val(), __builtin_nan(""), __builtin_nans(""), __DBL_DENORM_MIN__
		);
#endif	// #if !defined(__DBL_DENORM_MIN__)
#if !defined(__LDBL_DENORM_MIN__)
	SPROUT_NUMERIC_LIMITS_FLOATING_POINT_SPECIALIZED_DECL(
		long double,
		LDBL_MIN, LDBL_MAX,
		LDBL_EPSILON, 0.5L,
		INFINITY, NAN, NAN, LDBL_MIN
		);
#else	// #if !defined(__LDBL_DENORM_MIN__)
	SPROUT_NUMERIC_LIMITS_FLOATING_POINT_SPECIALIZED_DECL(
		long double,
		LDBL_MIN, LDBL_MAX,
		LDBL_EPSILON, 0.5L,
		__builtin_huge_vall(), __builtin_nanl(""), __builtin_nansl(""), __LDBL_DENORM_MIN__
		);
#endif	// #if !defined(__LDBL_DENORM_MIN__)
#undef SPROUT_NUMERIC_LIMITS_FLOATING_POINT_SPECIALIZED_DECL

#else	// #ifdef SPROUT_NO_CXX11_NUMERIC_LIMITS

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using numeric_limits = std::numeric_limits<T>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	class numeric_limits
		: public std::numeric_limits<T>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#endif	// #ifdef SPROUT_NO_CXX11_NUMERIC_LIMITS
}	// namespace sprout

#endif	// #ifndef SPROUT_LIMITS_HPP
