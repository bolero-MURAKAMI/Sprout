#ifndef SPROUT_RANGE_ALGORITHM_COUNT_IF_HPP
#define SPROUT_RANGE_ALGORITHM_COUNT_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/count_if.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.9 Count
		template<typename Range, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Range const>::difference_type
		count_if(Range const& range, Predicate pred) {
			return sprout::count_if(sprout::begin(range), sprout::end(range), pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_COUNT_IF_HPP
