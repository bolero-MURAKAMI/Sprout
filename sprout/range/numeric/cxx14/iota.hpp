/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_CXX14_IOTA_HPP
#define SPROUT_RANGE_NUMERIC_CXX14_IOTA_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/numeric/cxx14/iota.hpp>

namespace sprout {
	namespace range {
		//
		// iota
		//
		template<typename ForwardRange, typename T>
		inline SPROUT_CXX14_CONSTEXPR void
		iota(ForwardRange&& rng, T value) {
			sprout::iota(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng)), value);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_CXX14_IOTA_HPP
