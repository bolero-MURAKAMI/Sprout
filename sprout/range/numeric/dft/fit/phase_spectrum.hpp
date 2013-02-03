#ifndef SPROUT_RANGE_NUMERIC_DFT_FIT_PHASE_SPECTRUM_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIT_PHASE_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/numeric/dft/fit/phase_spectrum.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// phase_spectrum
			//
			template<typename InputRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			phase_spectrum(InputRange const& rng, Result const& result) {
				return sprout::fit::phase_spectrum(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename InputRange>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			phase_spectrum(InputRange const& rng) {
				return sprout::fit::phase_spectrum<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIT_PHASE_SPECTRUM_HPP
