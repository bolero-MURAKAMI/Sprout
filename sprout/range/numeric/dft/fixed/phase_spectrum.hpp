/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_PHASE_SPECTRUM_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIXED_PHASE_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/numeric/dft/fixed/phase_spectrum.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// phase_spectrum
			//
			template<
				typename InputRange, typename Result,
				typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			phase_spectrum(InputRange const& rng, Result const& result) {
				return sprout::fixed::phase_spectrum(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename InputRange>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			phase_spectrum(InputRange const& rng) {
				return sprout::fixed::phase_spectrum<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fixed

		using sprout::range::fixed::phase_spectrum;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_PHASE_SPECTRUM_HPP
