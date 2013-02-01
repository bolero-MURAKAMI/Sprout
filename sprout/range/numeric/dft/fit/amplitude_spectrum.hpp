#ifndef SPROUT_RANGE_NUMERIC_DFT_FIT_AMPLITUDE_SPECTRUM_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIT_AMPLITUDE_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/numeric/dft/fit/amplitude_spectrum.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// amplitude_spectrum
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			amplitude_spectrum(Input const& input, Result const& result) {
				return sprout::fit::amplitude_spectrum(sprout::begin(input), sprout::end(input), result);
			}

			template<typename Result, typename Input>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			amplitude_spectrum(Input const& input) {
				return sprout::fit::amplitude_spectrum<Result>(sprout::begin(input), sprout::end(input));
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIT_AMPLITUDE_SPECTRUM_HPP
