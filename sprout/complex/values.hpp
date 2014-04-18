/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_VALUES_HPP
#define SPROUT_COMPLEX_VALUES_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/operators.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/atan2.hpp>
#include <sprout/math/sqrt.hpp>

namespace sprout {
	template<typename T>
	SPROUT_CONSTEXPR T
	norm(sprout::complex<T> const& x);

	// 26.4.7, values:
	template<typename T>
	inline SPROUT_CONSTEXPR T const&
	real(sprout::complex<T> const& x) {
		return x.real();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR T const&
	imag(sprout::complex<T> const& x) {
		return x.imag();
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
	template<typename T>
	inline SPROUT_CONSTEXPR T
	norm(sprout::complex<T> const& x) {
		return x.real() * x.real() + x.imag() * x.imag();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	conj(sprout::complex<T> const& x) {
		return sprout::complex<T>(x.real(), -x.imag());
	}
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T>
		proj_impl(sprout::complex<T> const& x, T const& den) {
			return sprout::complex<T>(
				T(2) * x.real() / den,
				T(2) * x.imag() / den
				);
		}
	}	// detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	proj(sprout::complex<T> const& x) {
		return sprout::detail::proj_impl(
			x,
			sprout::norm(x) + T(1)
			);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	polar(T const& rho, T const& theta = 0) {
		return sprout::complex<T>(rho * sprout::cos(theta), rho * sprout::sin(theta));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_VALUES_HPP
