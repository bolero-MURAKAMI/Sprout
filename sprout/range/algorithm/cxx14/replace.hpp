/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_REPLACE_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_REPLACE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/cxx14/replace.hpp>

namespace sprout {
	namespace range {
		//
		// replace
		//
		template<typename ForwardRange, typename T>
		inline SPROUT_CXX14_CONSTEXPR void
		replace(ForwardRange&& rng, T const& old_value, T const& new_value) {
			sprout::replace(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng)), old_value, new_value);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_REPLACE_HPP
