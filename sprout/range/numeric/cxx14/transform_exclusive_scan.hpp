/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_CXX14_TRANSFORM_EXCLUSIVE_SCAN_HPP
#define SPROUT_RANGE_NUMERIC_CXX14_TRANSFORM_EXCLUSIVE_SCAN_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/numeric/cxx14/transform_exclusive_scan.hpp>

namespace sprout {
	namespace range {
		//
		// transform_exclusive_scan
		//
		template<
			typename InputRange, typename OutputIterator, typename T, typename BinaryOperation, typename UnaryOperation,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR OutputIterator
		transform_exclusive_scan(InputRange const& rng, OutputIterator result, T init, BinaryOperation binary_op, UnaryOperation unary_op) {
			return sprout::transform_exclusive_scan(sprout::begin(rng), sprout::end(rng), result, init, binary_op, unary_op);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_CXX14_TRANSFORM_EXCLUSIVE_SCAN_HPP
