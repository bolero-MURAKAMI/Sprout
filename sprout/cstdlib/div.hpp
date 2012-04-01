#ifndef SPROUT_CSTDLIB_DIV_HPP
#define SPROUT_CSTDLIB_DIV_HPP

#include <cstddef>
#include <cstdlib>
#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
#		define SPROUT_DIV_T_TRAITS_IMPL(DIV_T) \
		typedef DIV_T type; \
		static SPROUT_CONSTEXPR std::size_t offsetof_quot = offsetof(DIV_T, quot); \
		static SPROUT_CONSTEXPR std::size_t offsetof_rem = offsetof(DIV_T, rem);

		template<typename T>
		struct div_t_traits {};
		template<>
		struct div_t_traits<int> {
		public:
			SPROUT_DIV_T_TRAITS_IMPL(std::div_t);
		};
		template<>
		struct div_t_traits<long> {
		public:
			SPROUT_DIV_T_TRAITS_IMPL(std::ldiv_t);
		};
		template<>
		struct div_t_traits<long long> {
		public:
			SPROUT_DIV_T_TRAITS_IMPL(std::lldiv_t);
		};
#		undef SPROUT_DIV_T_TRAITS_IMPL

		extern void* enabler;

		template<
			typename T,
			typename std::enable_if<
				sprout::detail::div_t_traits<T>::offsetof_quot == 0
			>::type*& = sprout::detail::enabler
		>
		SPROUT_CONSTEXPR typename sprout::detail::div_t_traits<T>::type div_impl(T const& numer, T const& denom) {
			return {numer / denom, numer % denom};
		}

		template<
			typename T,
			typename std::enable_if<
				sprout::detail::div_t_traits<T>::offsetof_rem == 0
			>::type*& = sprout::detail::enabler
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

	SPROUT_CONSTEXPR std::lldiv_t lldiv(long long  numer, long long denom) {
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
