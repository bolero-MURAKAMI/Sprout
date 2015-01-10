/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_ROTATE_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_ROTATE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/cxx14/rotate.hpp>

namespace sprout {
	namespace range {
		//
		// rotate
		//
		template<typename ForwardRange>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange>::type
		rotate(ForwardRange&& rng, typename sprout::container_traits<typename::std::remove_reference<ForwardRange>::type>::iterator middle) {
			return sprout::range::range_return<ForwardRange>::pack(
				sprout::rotate(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), middle, sprout::end(SPROUT_FORWARD(ForwardRange, rng))),
				SPROUT_FORWARD(ForwardRange, rng)
				);
		}

		template<sprout::range::range_return_value RetV, typename ForwardRange>
		inline SPROUT_CXX14_CONSTEXPR typename sprout::range::range_return<ForwardRange, RetV>::type
		rotate(ForwardRange&& rng, typename sprout::container_traits<typename::std::remove_reference<ForwardRange>::type>::iterator middle) {
			return sprout::range::range_return<ForwardRange, RetV>::pack(
				sprout::rotate(sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), middle, sprout::end(SPROUT_FORWARD(ForwardRange, rng))),
				SPROUT_FORWARD(ForwardRange, rng)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_ROTATE_HPP
