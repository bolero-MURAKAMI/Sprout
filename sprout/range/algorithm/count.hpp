#ifndef SPROUT_RANGE_ALGORITHM_COUNT_HPP
#define SPROUT_RANGE_ALGORITHM_COUNT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/count.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.2.9 Count
		template<typename InputRange, typename T>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<InputRange const>::difference_type
		count(InputRange const& range, T const& value) {
			return sprout::count(sprout::begin(range), sprout::end(range), value);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_COUNT_HPP
