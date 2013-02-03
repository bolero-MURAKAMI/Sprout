#ifndef SPROUT_RANGE_NUMERIC_DFT_FIT_SPECTRUM_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIT_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/numeric/dft/fit/spectrum.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// spectrum
			//
			template<typename InputRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			spectrum(InputRange const& rng, Result const& result) {
				return sprout::fit::spectrum(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename InputRange>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			spectrum(InputRange const& rng) {
				return sprout::fit::spectrum<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#include <sprout/range/numeric/dft/fit/amplitude_spectrum.hpp>
#include <sprout/range/numeric/dft/fit/phase_spectrum.hpp>

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIT_SPECTRUM_HPP
