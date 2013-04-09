#ifndef SPROUT_RANGE_ALGORITHM_FIT_SET_SYMMETRIC_DIFFERENCE_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_SET_SYMMETRIC_DIFFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/set_symmetric_difference.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// set_symmetric_difference
			//
			template<typename InputRange1, typename InputRange2, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			set_symmetric_difference(InputRange1 const& rng1, InputRange2 const& rng2, Result const& result, Compare comp) {
				return sprout::fit::set_symmetric_difference(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2), result, comp);
			}
			template<typename InputRange1, typename InputRange2, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			set_symmetric_difference(InputRange1 const& rng1, InputRange2 const& rng2, Result const& result) {
				return sprout::fit::set_symmetric_difference(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2), result);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_SET_SYMMETRIC_DIFFERENCE_HPP
