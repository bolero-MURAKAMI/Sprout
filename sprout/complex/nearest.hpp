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
		return sprout::complex<T>(sprout::ceil(x.real()), sprout::ceil(x.imag()));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	floor(sprout::complex<T> const& x) {
		return sprout::complex<T>(sprout::floor(x.real()), sprout::floor(x.imag()));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	trunc(sprout::complex<T> const& x) {
		return sprout::complex<T>(sprout::math::trunc(x.real()), sprout::math::trunc(x.imag()));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::complex<T>
	round(sprout::complex<T> const& x) {
		return sprout::complex<T>(sprout::round(x.real()), sprout::round(x.imag()));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_NEAREST_HPP
