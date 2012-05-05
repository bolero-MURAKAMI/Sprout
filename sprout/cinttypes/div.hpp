#ifndef SPROUT_CINTTYPES_DIV_HPP
#define SPROUT_CINTTYPES_DIV_HPP

#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <cinttypes>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/enabler_if.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		struct div_t_traits2 {};

#	define SPROUT_DETAIL_DIV_T_TRAITS2_IMPL(INT_T, DIV_T) \
		template<> \
		struct div_t_traits2<INT_T> { \
		public: \
			typedef DIV_T type; \
			static SPROUT_CONSTEXPR std::size_t offsetof_quot = offsetof(DIV_T, quot); \
			static SPROUT_CONSTEXPR std::size_t offsetof_rem = offsetof(DIV_T, rem); \
		}

		SPROUT_DETAIL_DIV_T_TRAITS2_IMPL(std::intmax_t, std::imaxdiv_t);
#	undef SPROUT_DETAIL_DIV_T_TRAITS2_IMPL

		template<
			typename T,
			typename sprout::enabler_if<
				sprout::detail::div_t_traits2<T>::offsetof_quot == 0
			>::type = sprout::enabler
		>
		SPROUT_CONSTEXPR typename sprout::detail::div_t_traits2<T>::type div_impl2(T const& numer, T const& denom) {
			return {numer / denom, numer % denom};
		}

		template<
			typename T,
			typename sprout::enabler_if<
				sprout::detail::div_t_traits2<T>::offsetof_rem == 0
			>::type = sprout::enabler
		>
		SPROUT_CONSTEXPR typename sprout::detail::div_t_traits2<T>::type div_impl2(T const &numer, T const& denom) {
			return {numer % denom, numer / denom};
		}
	}	// namespace detail

	SPROUT_CONSTEXPR std::imaxdiv_t imaxdiv(std::intmax_t numer, std::intmax_t denom) {
		return sprout::detail::div_impl2(numer, denom);
	}

	template<
		typename T,
		typename sprout::enabler_if<std::is_same<T, std::intmax_t>::value>::type = sprout::enabler
	>
	SPROUT_CONSTEXPR std::imaxdiv_t div(T numer, T denom) {
		return sprout::imaxdiv(numer, denom);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CINTTYPES_DIV_HPP
