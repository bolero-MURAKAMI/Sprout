/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_COPY_UNTIL_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_COPY_UNTIL_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/copy_until.hpp>

namespace sprout {
	namespace range {
		//
		// copy_until
		//
		template<
			typename InputRange, typename OutputIterator, typename Predicate,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR OutputIterator
		copy_until(InputRange const& rng, OutputIterator result, Predicate pred) {
			return sprout::copy_until(sprout::begin(rng), sprout::end(rng), result, pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_COPY_UNTIL_HPP
