#ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_DFT_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIXED_DFT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/numeric/dft/fixed/dft.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// dft
			//
			template<typename ForwardRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			dft(ForwardRange const& rng, Result const& result) {
				return sprout::fixed::dft(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename ForwardRange>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			dft(ForwardRange const& rng) {
				return sprout::fixed::dft<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fixed

		using sprout::range::fixed::dft;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_DFT_HPP
