#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/remove_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// remove_copy
			//
			template<typename InputRange, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			remove_copy(InputRange const& rng, Result const& result, T const& value) {
				return sprout::fixed::remove_copy(sprout::begin(rng), sprout::end(rng), result, value);
			}

			template<typename Result, typename InputRange, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			remove_copy(InputRange const& rng, T const& value) {
				return sprout::fixed::remove_copy<Result>(sprout::begin(rng), sprout::end(rng), value);
			}
		}	// namespace fixed

		using sprout::range::fixed::remove_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_HPP
