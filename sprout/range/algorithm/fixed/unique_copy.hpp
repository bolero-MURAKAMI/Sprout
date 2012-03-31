#ifndef SPROUT_RANGE_ALGORITHM_FIXED_UNIQUE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_UNIQUE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/unique_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// unique_copy
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type unique_copy(
				Input const& input,
				Result const& result
				)
			{
				return sprout::fixed::unique_copy(sprout::begin(input), sprout::end(input), result);
			}

			//
			// unique_copy
			//
			template<typename Input, typename Result, typename BinaryPredicate>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type unique_copy(
				Input const& input,
				Result const& result,
				BinaryPredicate pred
				)
			{
				return sprout::fixed::unique_copy(sprout::begin(input), sprout::end(input), result, pred);
			}
		}	// namespace fixed

		using sprout::range::fixed::unique_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_UNIQUE_COPY_HPP
