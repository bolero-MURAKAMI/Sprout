#ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_SPECTRUM_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIXED_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/numeric/dft/fixed/spectrum.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// spectrum
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			spectrum(Input const& input, Result const& result) {
				return sprout::fixed::spectrum(sprout::begin(input), sprout::end(input), result);
			}

			template<typename Result, typename Input>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			spectrum(Input const& input) {
				return sprout::fixed::spectrum<Result>(sprout::begin(input), sprout::end(input));
			}
		}	// namespace fixed

		using sprout::range::fixed::spectrum;
	}	// namespace range
}	// namespace sprout

#include <sprout/range/numeric/dft/fixed/amplitude_spectrum.hpp>
#include <sprout/range/numeric/dft/fixed/phase_spectrum.hpp>

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_SPECTRUM_HPP
