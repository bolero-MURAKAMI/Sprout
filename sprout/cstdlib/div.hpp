#ifndef SPROUT_CSTDLIB_DIV_HPP
#define SPROUT_CSTDLIB_DIV_HPP

#include <cstddef>
#include <cstdlib>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/enabler_if.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		template<typename T>
		struct div_t_traits {};

#	define SPROUT_DETAIL_DIV_T_TRAITS_IMPL(INT_T, DIV_T) \
		template<> \
		struct div_t_traits<INT_T> { \
		public: \
			typedef DIV_T type; \
			static SPROUT_CONSTEXPR std::size_t offsetof_quot = offsetof(DIV_T, quot); \
			static SPROUT_CONSTEXPR std::size_t offsetof_rem = offsetof(DIV_T, rem); \
		}

		SPROUT_DETAIL_DIV_T_TRAITS_IMPL(int, std::div_t);
		SPROUT_DETAIL_DIV_T_TRAITS_IMPL(long, std::ldiv_t);
		SPROUT_DETAIL_DIV_T_TRAITS_IMPL(long long, std::lldiv_t);
#	undef SPROUT_DETAIL_DIV_T_TRAITS_IMPL

		template<
			typename T,
			typename sprout::enabler_if<
				sprout::detail::div_t_traits<T>::offsetof_quot == 0
			>::type = sprout::enabler
		>
		SPROUT_CONSTEXPR typename sprout::detail::div_t_traits<T>::type div_impl(T const& numer, T const& denom) {
			return {numer / denom, numer % denom};
		}

		template<
			typename T,
			typename sprout::enabler_if<
				sprout::detail::div_t_traits<T>::offsetof_rem == 0
			>::type = sprout::enabler
		>
		SPROUT_CONSTEXPR typename sprout::detail::div_t_traits<T>::type div_impl(T const &numer, T const& denom) {
			return {numer % denom, numer / denom};
		}
	}	// namespace detail

	// 7.20.6.2  divÅCldivÅCãyÇ— lldiv ä÷êî
	SPROUT_CONSTEXPR std::div_t div(int numer, int denom) {
		return sprout::detail::div_impl(numer, denom);
	}

	SPROUT_CONSTEXPR std::ldiv_t ldiv(long numer, long denom) {
		return sprout::detail::div_impl(numer, denom);
	}

	SPROUT_CONSTEXPR std::lldiv_t lldiv(long long numer, long long denom) {
		return sprout::detail::div_impl(numer, denom);
	}

	SPROUT_CONSTEXPR std::ldiv_t div(long numer, long denom) {
		return sprout::ldiv(numer, denom);
	}

	SPROUT_CONSTEXPR std::lldiv_t div(long long numer, long long denom) {
		return sprout::lldiv(numer, denom);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_DIV_HPP
