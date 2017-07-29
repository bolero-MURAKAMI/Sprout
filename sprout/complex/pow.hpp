/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_POW_HPP
#define SPROUT_COMPLEX_POW_HPP

#include <sprout/config.hpp>
#include <sprout/math/pow.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/arithmetic_operators.hpp>
#include <sprout/complex/exp.hpp>
#include <sprout/complex/log.hpp>

namespace sprout {
	//
	// pow
	//
	// G.6.4.1 The cpow functions
	// 1 The cpow functions raise floating-point exceptions if appropriate for the calculation of
	//   the parts of the result, and may raise spurious exceptions.317)
	//
	// 317) This allows cpow(z, c) to be implemented as cexp(c clog(z)) without precluding
	//      implementations that treat special cases more carefully.
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	pow(sprout::complex<T> const& x, sprout::complex<T> const& y) {
		return x == T() ? T()
			: sprout::exp(y * sprout::log(x))
			;
	}
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::complex<T> pow_impl(sprout::complex<T> const& t, T const& y) {
			return sprout::polar(sprout::exp(y * t.real()), y * t.imag());
		}
	}	// namespace detail
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	pow(sprout::complex<T> const& x, T const& y) {
		return x == T() ? T()
			: x.imag() == T() && x.real() > T() ? sprout::math::pow(x.real(), y)
			: sprout::detail::pow_impl(sprout::log(x), y)
			;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	pow(T const& x, sprout::complex<T> const& y) {
		return x > T() ? sprout::polar(sprout::pow(x, y.real()), y.imag() * sprout::log(x))
			: sprout::pow(sprout::complex<T>(x), y)
			;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_POW_HPP
