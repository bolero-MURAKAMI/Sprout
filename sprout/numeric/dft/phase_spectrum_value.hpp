/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_PHASE_SPECTRUM_VALUE_HPP
#define SPROUT_NUMERIC_DFT_PHASE_SPECTRUM_VALUE_HPP

#include <sprout/config.hpp>
#include <sprout/complex.hpp>
#include <sprout/math/atan2.hpp>
#include <sprout/math/llround.hpp>

namespace sprout {
	//
	// phase_spectrum_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename T::value_type
	phase_spectrum_value(T const& x) {
		using sprout::real;
		using sprout::imag;
		return sprout::atan2(sprout::llround(imag(x)), sprout::llround(real(x)));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_PHASE_SPECTRUM_VALUE_HPP
