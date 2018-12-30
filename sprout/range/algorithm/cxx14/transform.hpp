/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_CXX14_TRANSFORM_HPP
#define SPROUT_RANGE_ALGORITHM_CXX14_TRANSFORM_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/transform.hpp>

namespace sprout {
	namespace range {
		//
		// transform
		//
		template<
			typename InputRange, typename OutputIterator, typename UnaryOperation,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR OutputIterator
		transform(InputRange const& rng, OutputIterator result, UnaryOperation op) {
			return sprout::transform(sprout::begin(rng), sprout::end(rng), result, op);
		}
		template<
			typename InputRange1, typename InputRange2, typename OutputIterator, typename BinaryOperation,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CXX14_CONSTEXPR OutputIterator
		transform(InputRange1 const& rng1, InputRange2 const& rng2, OutputIterator result, BinaryOperation op) {
			return sprout::transform(sprout::begin(rng1), sprout::end(rng1), sprout::begin(rng2), result, op);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_CXX14_TRANSFORM_HPP
