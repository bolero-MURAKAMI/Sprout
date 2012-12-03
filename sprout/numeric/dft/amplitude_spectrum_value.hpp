#ifndef SPROUT_NUMERIC_DFT_AMPLITUDE_SPECTRUM_VALUE_HPP
#define SPROUT_NUMERIC_DFT_AMPLITUDE_SPECTRUM_VALUE_HPP

#include <sprout/config.hpp>
#include <sprout/complex.hpp>
#include <sprout/math/sqrt.hpp>

namespace sprout {
	//
	// amplitude_spectrum_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename T::value_type
	amplitude_spectrum_value(T const& x) {
		using sprout::real;
		using sprout::imag;
		return sprout::sqrt(real(x) * real(x) + imag(x) * imag(x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_AMPLITUDE_SPECTRUM_VALUE_HPP
