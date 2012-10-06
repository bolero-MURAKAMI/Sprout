#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/reverse_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// reverse_copy
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			reverse_copy(Input const& input, Result const& result) {
				return sprout::fixed::reverse_copy(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fixed

		using sprout::range::fixed::reverse_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP
