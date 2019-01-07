/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_REPLACE_COPY_IF_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_REPLACE_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/replace_copy_if.hpp>

namespace sprout {
	namespace range {
		//
		// replace_copy_if
		//
		template<
			typename InputRange, typename OutputIterator, typename T, typename Predicate,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR OutputIterator
		replace_copy_if(InputRange const& rng, OutputIterator result, Predicate pred, T const& new_value) {
			return sprout::replace_copy_if(sprout::begin(rng), sprout::end(rng), result, pred, new_value);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_REPLACE_COPY_IF_HPP
