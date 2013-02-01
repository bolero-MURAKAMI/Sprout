#ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_AMPLITUDE_SPECTRUM_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIXED_AMPLITUDE_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/numeric/dft/fixed/amplitude_spectrum.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// amplitude_spectrum
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			amplitude_spectrum(Input const& input, Result const& result) {
				return sprout::fixed::amplitude_spectrum(sprout::begin(input), sprout::end(input), result);
			}

			template<typename Result, typename Input>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			amplitude_spectrum(Input const& input) {
				return sprout::fixed::amplitude_spectrum<Result>(sprout::begin(input), sprout::end(input));
			}
		}	// namespace fixed

		using sprout::range::fixed::amplitude_spectrum;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_AMPLITUDE_SPECTRUM_HPP
