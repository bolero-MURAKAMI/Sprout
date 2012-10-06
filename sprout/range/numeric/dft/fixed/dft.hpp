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
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			dft(Input const& input, Result const& result) {
				return sprout::fixed::dft(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fixed

		using sprout::range::fixed::dft;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIXED_DFT_HPP
