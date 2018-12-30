/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_SET_INTERSECTION_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_SET_INTERSECTION_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/set_intersection.hpp>

namespace sprout {
	namespace range {
		//
		// set_intersection
		//
		template<
			typename InputRange1, typename InputRange2, typename OutputIterator, typename Compare,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR OutputIterator
		set_intersection(InputRange1 const& rng1, InputRange2 const& rng2, OutputIterator result, Compare comp) {
			return sprout::set_intersection(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2), result, comp);
		}
		template<
			typename InputRange1, typename InputRange2, typename OutputIterator,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR OutputIterator
		set_intersection(InputRange1 const& rng1, InputRange2 const& rng2, OutputIterator result) {
			return sprout::set_intersection(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), sprout::end(rng2), result);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_SET_INTERSECTION_HPP
