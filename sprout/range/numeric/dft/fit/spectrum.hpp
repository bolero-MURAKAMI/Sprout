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
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			spectrum(Input const& input, Result const& result) {
				return sprout::fit::spectrum(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#include <sprout/range/numeric/dft/fit/amplitude_spectrum.hpp>
#include <sprout/range/numeric/dft/fit/phase_spectrum.hpp>

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIT_SPECTRUM_HPP
