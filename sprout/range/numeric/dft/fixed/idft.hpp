/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_IDFT_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIXED_IDFT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/numeric/dft/fixed/idft.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// idft
			//
			template<typename ForwardRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			idft(ForwardRange const& rng, Result const& result) {
				return sprout::fixed::idft(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename ForwardRange>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			idft(ForwardRange const& rng) {
				return sprout::fixed::idft<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fixed

		using sprout::range::fixed::idft;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_IDFT_HPP
