/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_FOR_EACH_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_FOR_EACH_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/cxx14/for_each.hpp>

namespace sprout {
	namespace range {
		//
		// for_each
		//
		template<typename InputRange, typename Function>
		inline SPROUT_CXX14_CONSTEXPR Function
		for_each(InputRange&& rng, Function f) {
			return sprout::for_each(sprout::begin(SPROUT_FORWARD(InputRange, rng)), sprout::end(SPROUT_FORWARD(InputRange, rng)), f);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_FOR_EACH_HPP
