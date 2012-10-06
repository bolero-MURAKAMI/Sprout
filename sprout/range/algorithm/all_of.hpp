#ifndef SPROUT_RANGE_ALGORITHM_ALL_OF_HPP
#define SPROUT_RANGE_ALGORITHM_ALL_OF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/all_of.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.1 All of
		template<typename Range, typename Predicate>
		inline SPROUT_CONSTEXPR bool
		all_of(Range const& range, Predicate pred) {
			return sprout::all_of(sprout::begin(range), sprout::end(range), pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_ALL_OF_HPP
