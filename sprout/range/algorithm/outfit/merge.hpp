#ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_MERGE_HPP
#define SPROUT_RANGE_ALGORITHM_OUTFIT_MERGE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/outfit/merge.hpp>

namespace sprout {
	namespace range {
		namespace outfit {
			//
			// merge
			//
			template<typename Input1, typename Input2, typename Result, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type merge(
				Input1 const& input1,
				Input2 const& input2,
				Result const& result,
				Compare comp
				)
			{
				return sprout::outfit::merge(sprout::begin(input1), sprout::end(input1), sprout::begin(input2), sprout::end(input2), result, comp);
			}

			//
			// merge
			//
			template<typename Input1, typename Input2, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type merge(
				Input1 const& input1,
				Input2 const& input2,
				Result const& result
				)
			{
				return sprout::outfit::merge(sprout::begin(input1), sprout::end(input1), sprout::begin(input2), sprout::end(input2), result);
			}
		}	// namespace outfit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_MERGE_HPP
