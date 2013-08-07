#ifndef SPROUT_RANGE_ALGORITHM_INCLUDES_HPP
#define SPROUT_RANGE_ALGORITHM_INCLUDES_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/includes.hpp>

namespace sprout {
	namespace range {
		// Copyright (C) 2011 RiSK (sscrisk)

		// 25.4.5.1 includes
		template<typename InputRange1, typename InputRange2>
		inline SPROUT_CONSTEXPR bool
		includes(InputRange1 const& range1, InputRange2 const& range2) {
			return sprout::includes(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2));
		}

		template<typename InputRange1, typename InputRange2, typename Compare>
		inline SPROUT_CONSTEXPR bool
		includes(InputRange1 const& range1, InputRange2 const& range2, Compare comp) {
			return sprout::includes(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2), comp);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_INCLUDES_HPP
