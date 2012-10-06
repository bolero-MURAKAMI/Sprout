#ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_PHASE_SPECTRUM_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIXED_PHASE_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/numeric/dft/fixed/phase_spectrum.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// phase_spectrum
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			phase_spectrum(Input const& input, Result const& result) {
				return sprout::fixed::phase_spectrum(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fixed

		using sprout::range::fixed::phase_spectrum;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_PHASE_SPECTRUM_HPP
