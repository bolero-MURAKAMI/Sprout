/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_CXX14_EXCLUSIVE_SCAN_HPP
#define SPROUT_RANGE_NUMERIC_CXX14_EXCLUSIVE_SCAN_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/numeric/cxx14/exclusive_scan.hpp>

namespace sprout {
	namespace range {
		//
		// exclusive_scan
		//
		template<
			typename InputRange, typename OutputIterator, typename T,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR OutputIterator
		exclusive_scan(InputRange const& rng, OutputIterator result, T init) {
			return sprout::exclusive_scan(sprout::begin(rng), sprout::end(rng), result, init);
		}
		template<
			typename InputRange, typename OutputIterator, typename T, typename BinaryOperation,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR OutputIterator
		exclusive_scan(InputRange const& rng, OutputIterator result, T init, BinaryOperation binary_op) {
			return sprout::exclusive_scan(sprout::begin(rng), sprout::end(rng), result, init, binary_op);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_CXX14_EXCLUSIVE_SCAN_HPP
