#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_UNTIL_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_UNTIL_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy_until.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy_until
			//
			template<typename InputRange, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_until(InputRange const& rng, Result const& result, Predicate pred) {
				return sprout::fixed::copy_until(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename InputRange, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_until(InputRange const& rng, Predicate pred) {
				return sprout::fixed::copy_until<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fixed

		using sprout::range::fixed::copy_until;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_UNTIL_HPP
