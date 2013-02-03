#ifndef SPROUT_RANGE_NUMERIC_DFT_FIT_IDFT_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIT_IDFT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/numeric/dft/fit/idft.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// idft
			//
			template<typename ForwardRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			idft(ForwardRange const& rng, Result const& result) {
				return sprout::fit::idft(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename ForwardRange>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			idft(ForwardRange const& rng) {
				return sprout::fit::idft<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIT_IDFT_HPP
