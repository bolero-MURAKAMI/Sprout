/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_POLER_HPP
#define SPROUT_COMPLEX_POLER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/type_traits/complex_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// polar
	//
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		polar_impl(T const& x, T const& y) {
			return sprout::complex<T>(
				sprout::math::isnan(x) ? T() : x,
				sprout::math::isnan(y) ? T() : y
				);
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	polar(T const& rho, T const& theta = T()) {
		typedef sprout::complex<T> type;
		return sprout::math::isnan(rho) || sprout::math::signbit(rho)
				? type(sprout::numeric_limits<T>::quiet_NaN(), sprout::numeric_limits<T>::quiet_NaN())
			: sprout::math::isnan(theta)
				? sprout::math::isinf(rho) ? type(rho, theta)
				: type(theta, theta)
			: sprout::math::isinf(theta)
				? sprout::math::isinf(rho) ? type(rho, sprout::numeric_limits<T>::quiet_NaN())
				: type(sprout::numeric_limits<T>::quiet_NaN(), sprout::numeric_limits<T>::quiet_NaN())
			: sprout::detail::polar_impl(rho * sprout::math::cos(theta), rho * sprout::math::sin(theta))
			;
	}
	template<
		typename ArithmeticType1, typename ArithmeticType2,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::complex_promote<ArithmeticType1, ArithmeticType2>::type
	polar(ArithmeticType1 const& rho, ArithmeticType2 const& theta) {
		typedef typename sprout::complex_promote<ArithmeticType1, ArithmeticType2>::type::value_type value_type;
		return sprout::polar(static_cast<value_type>(rho), static_cast<value_type>(theta));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_POLER_HPP
