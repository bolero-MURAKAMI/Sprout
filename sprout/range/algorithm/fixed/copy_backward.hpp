#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_BACKWARD_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy_backward.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy_backward
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_backward(Input const& input, Result const& result) {
				return sprout::fixed::copy_backward(sprout::begin(input), sprout::end(input), result);
			}

			template<typename Result, typename Input>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_backward(Input const& input) {
				return sprout::fixed::copy_backward<Result>(sprout::begin(input), sprout::end(input));
			}
		}	// namespace fixed

		using sprout::range::fixed::copy_backward;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_BACKWARD_HPP
