#ifndef SPROUT_NUMERIC_DFT_FIT_SPECTRUM_HPP
#define SPROUT_NUMERIC_DFT_FIT_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/numeric/dft/fit/amplitude_spectrum.hpp>

namespace sprout {
	namespace fit {
		//
		// spectrum
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		spectrum(InputIterator first, InputIterator last, Result const& result) {
			return sprout::fit::amplitude_spectrum(first, last, result);
		}
	}	// namespace fit
}	// namespace sprout

#include <sprout/numeric/dft/fit/phase_spectrum.hpp>

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIT_SPECTRUM_HPP
