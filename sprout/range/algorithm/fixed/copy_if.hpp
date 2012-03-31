#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_IF_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy_if.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy_if
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_if(
				Input const& input,
				Result const& result
				)
			{
				return sprout::fixed::copy_if(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fixed

		using sprout::range::fixed::copy_if;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_IF_HPP
