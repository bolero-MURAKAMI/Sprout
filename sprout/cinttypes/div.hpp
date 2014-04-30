/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CINTTYPES_DIV_HPP
#define SPROUT_CINTTYPES_DIV_HPP

#include <cstdlib>
#include <cstdint>
#if !defined(_MSC_VER)
#	include <cinttypes>
#endif
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>

namespace sprout {
	//
	// imaxdiv_t
	//
#if defined(_MSC_VER)
	struct imaxdiv_t {
	public:
		std::intmax_t quot;
		std::intmax_t rem;
	};
#else
	typedef std::imaxdiv_t imaxdiv_t;
#endif

	namespace detail {
		template<typename T>
		struct div_t_traits2 {};

#	define SPROUT_DETAIL_DIV_T_TRAITS2_IMPL(INT_T, DIV_T) \
		template<> \
		struct div_t_traits2<INT_T> { \
		public: \
			typedef DIV_T type; \
			SPROUT_STATIC_CONSTEXPR std::size_t offsetof_quot = offsetof(DIV_T, quot); \
			SPROUT_STATIC_CONSTEXPR std::size_t offsetof_rem = offsetof(DIV_T, rem); \
		}

		SPROUT_DETAIL_DIV_T_TRAITS2_IMPL(std::intmax_t, sprout::imaxdiv_t);
#	undef SPROUT_DETAIL_DIV_T_TRAITS2_IMPL

		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::div_t_traits2<T>::offsetof_quot == 0,
			typename sprout::detail::div_t_traits2<T>::type
		>::type
		div_impl2(T const& numer, T const& denom) {
#if defined(_MSC_VER)
			typename sprout::detail::div_t_traits2<T>::type result = {numer / denom, numer % denom};
			return result;
#else
			return {numer / denom, numer % denom};
#endif
		}

		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::div_t_traits2<T>::offsetof_rem == 0,
			typename sprout::detail::div_t_traits2<T>::type
		>::type
		div_impl2(T const &numer, T const& denom) {
#if defined(_MSC_VER)
			typename sprout::detail::div_t_traits2<T>::type result = {numer % denom, numer / denom};
			return result;
#else
			return {numer % denom, numer / denom};
#endif
		}
	}	// namespace detail

	inline SPROUT_CONSTEXPR sprout::imaxdiv_t
	imaxdiv(std::intmax_t numer, std::intmax_t denom) {
		return sprout::detail::div_impl2(numer, denom);
	}

	template<typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<T, std::intmax_t>::value,
		sprout::imaxdiv_t
	>::type
	div(T numer, T denom) {
		return sprout::imaxdiv(numer, denom);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CINTTYPES_DIV_HPP
