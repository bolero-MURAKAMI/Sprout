#ifndef SPROUT_RANGE_ALGORITHM_ONE_OF_HPP
#define SPROUT_RANGE_ALGORITHM_ONE_OF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/one_of.hpp>

namespace sprout {
	namespace range {
		//
		// one_of
		//
		template<typename Range, typename Predicate>
		inline SPROUT_CONSTEXPR bool
		one_of(Range const& range, Predicate pred) {
			return sprout::one_of(sprout::begin(range), sprout::end(range), pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_ONE_OF_HPP
