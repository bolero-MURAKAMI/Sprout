/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_IS_SORTED_HPP
#define SPROUT_RANGE_ALGORITHM_IS_SORTED_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_sorted.hpp>

namespace sprout {
	namespace range {

		// 25.4.1.5 is_sorted
		template<typename ForwardRange>
		inline SPROUT_CONSTEXPR bool
		is_sorted(ForwardRange const& range) {
			return sprout::is_sorted(sprout::begin(range), sprout::end(range));
		}

		template<typename ForwardRange, typename Compare>
		inline SPROUT_CONSTEXPR bool
		is_sorted(ForwardRange const& range, Compare comp) {
			return sprout::is_sorted(sprout::begin(range), sprout::end(range), comp);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_SORTED_HPP
