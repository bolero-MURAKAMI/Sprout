#ifndef SPROUT_RANGE_ALGORITHM_FIXED_SET_UNION_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_SET_UNION_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/set_union.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// set_union
			//
			template<typename InputRange1, typename InputRange2, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			set_union(InputRange1 const& rng1, InputRange2 const& rng2, Result const& result, Compare comp) {
				return sprout::fixed::set_union(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2), result, comp);
			}
			template<typename InputRange1, typename InputRange2, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			set_union(InputRange1 const& rng1, InputRange2 const& rng2, Result const& result) {
				return sprout::fixed::set_union(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2), result);
			}

			template<typename Result, typename InputRange1, typename InputRange2, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			set_union(InputRange1 const& rng1, InputRange2 const& rng2, Compare comp) {
				return sprout::fixed::set_union<Result>(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2), comp);
			}
			template<typename Result, typename InputRange1, typename InputRange2>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			set_union(InputRange1 const& rng1, InputRange2 const& rng2) {
				return sprout::fixed::set_union<Result>(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2));
			}
		}	// namespace fixed

		using sprout::range::fixed::set_union;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_SET_UNION_HPP
