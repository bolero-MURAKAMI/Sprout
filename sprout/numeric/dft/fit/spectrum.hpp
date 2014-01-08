/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_FIT_SPECTRUM_HPP
#define SPROUT_NUMERIC_DFT_FIT_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/numeric/dft/fit/amplitude_spectrum.hpp>

namespace sprout {
	namespace fit {
		//
		// spectrum
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		spectrum(InputIterator first, InputIterator last, Result const& result) {
			return sprout::fit::amplitude_spectrum(first, last, result);
		}

		template<typename Result, typename InputIterator>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		spectrum(InputIterator first, InputIterator last) {
			return sprout::fit::amplitude_spectrum<Result>(first, last);
		}
	}	// namespace fit
}	// namespace sprout

#include <sprout/numeric/dft/fit/phase_spectrum.hpp>

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIT_SPECTRUM_HPP
