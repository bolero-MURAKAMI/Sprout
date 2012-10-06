#ifndef SPROUT_RANGE_ALGORITHM_FIXED_MERGE_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_MERGE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/merge.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// merge
			//
			template<typename Input1, typename Input2, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			merge(Input1 const& input1, Input2 const& input2, Result const& result, Compare comp) {
				return sprout::fixed::merge(sprout::begin(input1), sprout::end(input1), sprout::begin(input2), sprout::end(input2), result, comp);
			}
			template<typename Input1, typename Input2, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			merge(Input1 const& input1, Input2 const& input2, Result const& result) {
				return sprout::fixed::merge(sprout::begin(input1), sprout::end(input1), sprout::begin(input2), sprout::end(input2), result);
			}
		}	// namespace fixed

		using sprout::range::fixed::merge;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_MERGE_HPP
