#ifndef SPROUT_RANGE_ALGORITHM_FIXED_CLAMP_RANGE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_CLAMP_RANGE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/clamp_range_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// clamp_range_copy
			//
			template<typename Input, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			clamp_range_copy(
				Input const& input, Result const& result,
				typename sprout::container_traits<Input>::value_type const& low,
				typename sprout::container_traits<Input>::value_type const& high,
				Compare comp
				)
			{
				return sprout::fixed::clamp_range_copy(sprout::begin(input), sprout::end(input), result, low, high, comp);
			}
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			clamp_range_copy(
				Input const& input, Result const& result,
				typename sprout::container_traits<Input>::value_type const& low,
				typename sprout::container_traits<Input>::value_type const& high
				)
			{
				return sprout::fixed::clamp_range_copy(sprout::begin(input), sprout::end(input), result, low, high);
			}
		}	// namespace fixed

		using sprout::range::fixed::clamp_range_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_CLAMP_RANGE_COPY_HPP
