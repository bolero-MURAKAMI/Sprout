/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_REMOVE_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_REMOVE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/cxx14/remove.hpp>

namespace sprout {
	namespace range {
		//
		// remove
		//
		template<typename ForwardRange, typename T>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		remove(ForwardRange&& rng, T const& value) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::remove(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng)), value),
				SPROUT_FORWARD(ForwardRange, rng)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange, typename T>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		remove(ForwardRange&& rng, T const& value) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::remove(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng)), value),
				SPROUT_FORWARD(ForwardRange, rng)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_REMOVE_HPP
