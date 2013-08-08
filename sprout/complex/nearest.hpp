/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_NEAREST_HPP
#define SPROUT_COMPLEX_NEAREST_HPP

#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/math/ceil.hpp>
#include <sprout/math/floor.hpp>
#include <sprout/math/trunc.hpp>
#include <sprout/math/round.hpp>

namespace sprout {
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	ceil(sprout::complex<T> const& x) {
		return sprout::complex<T>(sprout::math::ceil(x.real()), sprout::math::ceil(x.imag()));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	floor(sprout::complex<T> const& x) {
		return sprout::complex<T>(sprout::math::floor(x.real()), sprout::math::floor(x.imag()));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	trunc(sprout::complex<T> const& x) {
		return sprout::complex<T>(sprout::math::trunc(x.real()), sprout::math::trunc(x.imag()));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	round(sprout::complex<T> const& x) {
		return sprout::complex<T>(sprout::math::round(x.real()), sprout::math::round(x.imag()));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_NEAREST_HPP
