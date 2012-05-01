#ifndef SPROUT_RANGE_NUMERIC_DFT_FIT_DFT_HPP
#define SPROUT_RANGE_NUMERIC_DFT_FIT_DFT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/numeric/dft/fit/dft.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// dft
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type dft(
				Input const& input,
				Result const& result
				)
			{
				return sprout::fit::dft(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_FIT_DFT_HPP
