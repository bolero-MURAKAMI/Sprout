#ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_UNIQUE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_OUTFIT_UNIQUE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/outfit/unique_copy.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace outfit {
			//
			// unique_copy
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> unique_copy(
				Input const& input,
				Result const& result
				)
			{
				return sprout::outfit::unique_copy(sprout::begin(input), sprout::end(input), result);
			}

			//
			// unique_copy
			//
			template<typename Input, typename Result, typename BinaryPredicate>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> unique_copy(
				Input const& input,
				Result const& result,
				BinaryPredicate pred
				)
			{
				return sprout::outfit::unique_copy(sprout::begin(input), sprout::end(input), result, pred);
			}
		}	// namespace outfit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_UNIQUE_COPY_HPP
