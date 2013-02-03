#ifndef SPROUT_RANGE_ALGORITHM_FIT_CLAMP_RANGE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_CLAMP_RANGE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/clamp_range_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// clamp_range_copy
			//
			template<typename InputRange, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			clamp_range_copy(
				InputRange const& rng, Result const& result,
				typename sprout::container_traits<InputRange>::value_type const& low,
				typename sprout::container_traits<InputRange>::value_type const& high,
				Compare comp
				)
			{
				return sprout::fit::clamp_range_copy(sprout::begin(rng), sprout::end(rng), result, low, high, comp);
			}
			template<typename InputRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			clamp_range_copy(
				InputRange const& rng, Result const& result,
				typename sprout::container_traits<InputRange>::value_type const& low,
				typename sprout::container_traits<InputRange>::value_type const& high
				)
			{
				return sprout::fit::clamp_range_copy(sprout::begin(rng), sprout::end(rng), result, low, high);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_CLAMP_RANGE_COPY_HPP
