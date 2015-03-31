/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_BINARY_SEARCH_HPP
#define SPROUT_RANGE_ALGORITHM_BINARY_SEARCH_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/binary_search.hpp>

namespace sprout {
	namespace range {

		// 25.4.3.4 binary_search
		template<typename ForwardRange, typename T>
		inline SPROUT_CONSTEXPR bool
		binary_search(ForwardRange const& range, T const& value) {
			return sprout::binary_search(sprout::begin(range), sprout::end(range), value);
		}

		template<typename ForwardRange, typename T, typename Compare>
		inline SPROUT_CONSTEXPR bool
		binary_search(ForwardRange const& range, T const& value, Compare comp) {
			return sprout::binary_search(sprout::begin(range), sprout::end(range), value, comp);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_BINARY_SEARCH_HPP
