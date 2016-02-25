/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_POW_HPP
#define SPROUT_DETAIL_POW_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/is_sint.hpp>
#include <sprout/type_traits/is_uint.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR T
		pow2(T const& x) {
			return x * x;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T
		pow3(T const& x) {
			return x * x * x;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T
		pow4(T const& x) {
			return x * x * x * x;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T
		pow5(T const& x) {
			return x * x * x * x * x;
		}

		template<typename T, typename IntType>
		inline SPROUT_CONSTEXPR T
		pow_n_impl(T const& x, IntType n) {
			return n == 1 ? x
				: n % 2 ? x * sprout::detail::pow2(sprout::detail::pow_n_impl(x, n / 2))
				: sprout::detail::pow2(sprout::detail::pow_n_impl(x, n / 2))
				;
		}
		template<
			typename T, typename UIntType,
			typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR T
		pow_n(T const& x, UIntType n) {
			return n == 0 ? T(1)
				: sprout::detail::pow_n_impl(x, n)
				;
		}
		template<
			typename T, typename IntType,
			typename sprout::enabler_if<sprout::is_sint<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR T
		pow_n(T const& x, IntType n) {
			return n == 0 ? T(1)
				: n > 0 ? sprout::detail::pow_n_impl(x, n)
				: T(1) / sprout::detail::pow_n_impl(x, -n)
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_POW_HPP
