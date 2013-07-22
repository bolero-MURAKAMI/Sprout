#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_IF_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy_if.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy_if
			//
			template<typename InputRange, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_if(InputRange const& rng, Result const& result, Predicate pred) {
				return sprout::fixed::copy_if(sprout::begin(rng), sprout::end(rng), result, pred);
			}

			template<typename Result, typename InputRange, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_if(InputRange const& rng, Predicate pred) {
				return sprout::fixed::copy_if<Result>(sprout::begin(rng), sprout::end(rng), pred);
			}
		}	// namespace fixed

		using sprout::range::fixed::copy_if;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_IF_HPP
