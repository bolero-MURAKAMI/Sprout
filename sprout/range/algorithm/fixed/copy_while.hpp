#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_WHILE_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_WHILE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy_while.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy_while
			//
			template<typename Input, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_while(Input const& input, Result const& result, Predicate pred) {
				return sprout::fixed::copy_while(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fixed

		using sprout::range::fixed::copy_while;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_WHILE_HPP
