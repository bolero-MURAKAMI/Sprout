/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_COUNT_HPP
#define SPROUT_RANGE_ALGORITHM_COUNT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/count.hpp>

namespace sprout {
	namespace range {

		// 25.2.9 Count
		template<typename InputRange, typename T>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<InputRange const>::difference_type
		count(InputRange const& range, T const& value) {
			return sprout::count(sprout::begin(range), sprout::end(range), value);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_COUNT_HPP
