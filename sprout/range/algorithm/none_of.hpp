#ifndef SPROUT_RANGE_ALGORITHM_NONE_OF_HPP
#define SPROUT_RANGE_ALGORITHM_NONE_OF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/none_of.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.3 None of
		template<typename Range, typename Predicate>
		SPROUT_CONSTEXPR bool none_of(Range const& range, Predicate pred) {
			return sprout::none_of(sprout::begin(range), sprout::end(range), pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_NONE_OF_HPP
