/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_VALUES_HPP
#define SPROUT_COMPLEX_VALUES_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/operators.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/atan2.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/complex_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	template<typename T>
	SPROUT_CONSTEXPR T
	norm(sprout::complex<T> const& x);

	//
	// 26.4.7, values:
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T const&
	real(sprout::complex<T> const& x) {
		return x.real();
	}
	template<
		typename ArithmeticType,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
	real(ArithmeticType x) {
		return x;
	}

	template<typename T>
	inline SPROUT_CONSTEXPR T const&
	imag(sprout::complex<T> const& x) {
		return x.imag();
	}
	template<
		typename ArithmeticType,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
	imag(ArithmeticType) {
		return 0;
	}

	template<typename T>
	inline SPROUT_CONSTEXPR T&
	real(sprout::complex<T>& x) {
		return x.real();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR T&
	imag(sprout::complex<T>& x) {
		return x.imag();
	}

	template<typename T>
	inline SPROUT_CONSTEXPR T
	abs(sprout::complex<T> const& x) {
		return sprout::sqrt(sprout::norm(x));
	}

	template<typename T>
	inline SPROUT_CONSTEXPR T
	arg(sprout::complex<T> const& x) {
		return sprout::atan2(x.imag(), x.real());
	}
	template<
		typename ArithmeticType,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
	arg(ArithmeticType x) {
		return sprout::atan2(ArithmeticType(0), x);
	}

	template<typename T>
	inline SPROUT_CONSTEXPR T
	norm(sprout::complex<T> const& x) {
		return x.real() * x.real() + x.imag() * x.imag();
	}
	template<
		typename ArithmeticType,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
	norm(ArithmeticType x) {
		typedef typename sprout::complex_promote<ArithmeticType>::type type;
		return type(x) * type(x);
	}

	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	conj(sprout::complex<T> const& x) {
		return sprout::complex<T>(x.real(), -x.imag());
	}
	template<
		typename ArithmeticType,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::complex_promote<ArithmeticType>::type
	conj(ArithmeticType x) {
		typedef typename sprout::complex_promote<ArithmeticType>::type type;
		return type(x);
	}

	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	proj(sprout::complex<T> const& x) {
		return sprout::math::isinf(x.real()) || sprout::math::isinf(x.imag())
			? sprout::complex<T>(sprout::numeric_limits<T>::infinity(), sprout::math::copysign(T(), x.imag()))
			: x
			;
	}
	template<
		typename ArithmeticType,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::complex_promote<ArithmeticType>::type
	proj(ArithmeticType x) {
		typedef typename sprout::complex_promote<ArithmeticType>::type type;
		return sprout::math::isinf(x)
			? type(sprout::numeric_limits<ArithmeticType>::infinity())
			: type(x)
			;
	}

	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		polar_impl(T const& x, T const& y) {
			typedef sprout::complex<T> type;
			return type(
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
			: sprout::detail::polar_impl(rho * sprout::cos(theta), rho * sprout::sin(theta))
			;
	}
	template<
		typename ArithmeticType1, typename ArithmeticType2,
		typename sprout::enabler_if<std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::complex_promote<ArithmeticType1, ArithmeticType2>::type
	polar(ArithmeticType1 const& rho, ArithmeticType2 const& theta) {
		typedef typename sprout::complex_promote<ArithmeticType1, ArithmeticType2>::type::value_type value_type;
		return sprout::polar<value_type>(rho, theta);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_VALUES_HPP
