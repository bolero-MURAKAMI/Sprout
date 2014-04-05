/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_CXX14_ADJACENT_DIFFERENCE_HPP
#define SPROUT_RANGE_NUMERIC_CXX14_ADJACENT_DIFFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/numeric/cxx14/adjacent_difference.hpp>

namespace sprout {
	namespace range {
		//
		// adjacent_difference
		//
		template<
			typename InputRange, typename OutputIterator,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR OutputIterator
		adjacent_difference(InputRange const& rng, OutputIterator result) {
			return sprout::adjacent_difference(sprout::begin(rng), sprout::end(rng), result);
		}
		template<
			typename InputRange, typename OutputIterator, typename BinaryOperation,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR OutputIterator
		adjacent_difference(InputRange const& rng, OutputIterator result, BinaryOperation binary_op) {
			return sprout::adjacent_difference(sprout::begin(rng), sprout::end(rng), result, binary_op);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_CXX14_ADJACENT_DIFFERENCE_HPP
