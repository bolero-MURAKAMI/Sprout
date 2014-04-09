/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_REMOVE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_REMOVE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/remove_copy.hpp>

namespace sprout {
	namespace range {
		//
		// remove_copy
		//
		template<
			typename InputRange, typename OutputIterator, typename T,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR OutputIterator
		remove_copy(InputRange const& rng, OutputIterator result, T const& value) {
			return sprout::remove_copy(sprout::begin(rng), sprout::end(rng), result, value);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_REMOVE_COPY_HPP
