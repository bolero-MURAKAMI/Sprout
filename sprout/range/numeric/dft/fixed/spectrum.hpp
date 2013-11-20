/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_SPECTRUM_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIXED_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/numeric/dft/fixed/spectrum.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// spectrum
			//
			template<typename InputRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			spectrum(InputRange const& rng, Result const& result) {
				return sprout::fixed::spectrum(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename InputRange>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			spectrum(InputRange const& rng) {
				return sprout::fixed::spectrum<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fixed

		using sprout::range::fixed::spectrum;
	}	// namespace range
}	// namespace sprout

#include <sprout/range/numeric/dft/fixed/amplitude_spectrum.hpp>
#include <sprout/range/numeric/dft/fixed/phase_spectrum.hpp>

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_SPECTRUM_HPP
