/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_NONE_OF_HPP
#define SPROUT_RANGE_ALGORITHM_NONE_OF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/none_of.hpp>

namespace sprout {
	namespace range {

		// 25.2.3 None of
		template<typename InputRange, typename Predicate>
		inline SPROUT_CONSTEXPR bool
		none_of(InputRange const& range, Predicate pred) {
			return sprout::none_of(sprout::begin(range), sprout::end(range), pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_NONE_OF_HPP
