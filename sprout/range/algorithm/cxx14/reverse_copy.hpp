/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_REVERSE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_REVERSE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/reverse_copy.hpp>

namespace sprout {
	namespace range {
		//
		// reverse_copy
		//
		template<
			typename BidirectionalRange, typename OutputIterator,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR OutputIterator
		reverse_copy(BidirectionalRange const& rng, OutputIterator result) {
			return sprout::reverse_copy(sprout::begin(rng), sprout::end(rng), result);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_REVERSE_COPY_HPP
