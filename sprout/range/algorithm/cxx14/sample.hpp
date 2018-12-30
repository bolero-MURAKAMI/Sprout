/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_SAMPLE_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_SAMPLE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/sample.hpp>

namespace sprout {
	namespace range {
		//
		// sample
		//
		template<
			typename PopRange, typename SampleIterator, typename Size, typename URNG,
			typename sprout::enabler_if<sprout::is_iterator_outputable<SampleIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR SampleIterator
		sample(PopRange const& rng, SampleIterator out, Size n, URNG&& g) {
			return sprout::sample(sprout::begin(rng), sprout::end(rng), out, n, SPROUT_FORWARD(URNG, g));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_SAMPLE_HPP
