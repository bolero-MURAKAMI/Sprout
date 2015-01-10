/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_REPLACE_IF_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_REPLACE_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/cxx14/replace_if.hpp>

namespace sprout {
	namespace range {
		//
		// replace_if
		//
		template<typename ForwardRange, typename Predicate, typename T>
		inline SPROUT_CXX14_CONSTEXPR void
		replace_if(ForwardRange&& rng, Predicate pred, T const& new_value) {
			sprout::replace_if(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng)), pred, new_value);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_REPLACE_IF_HPP
