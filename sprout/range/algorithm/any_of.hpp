#ifndef SPROUT_RANGE_ALGORITHM_ANY_OF_HPP
#define SPROUT_RANGE_ALGORITHM_ANY_OF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/any_of.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.2 Any of
		template<typename Range, typename Predicate>
		SPROUT_CONSTEXPR bool any_of(Range const& range, Predicate pred) {
			return sprout::any_of(sprout::begin(range), sprout::end(range), pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_ANY_OF_HPP
