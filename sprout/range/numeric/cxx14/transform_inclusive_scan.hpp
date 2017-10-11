/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_CXX14_TRANSFORM_INCLUSIVE_SCAN_HPP
#define SPROUT_RANGE_NUMERIC_CXX14_TRANSFORM_INCLUSIVE_SCAN_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/numeric/cxx14/transform_inclusive_scan.hpp>

namespace sprout {
	namespace range {
		//
		// transform_inclusive_scan
		//
		template<
			typename InputRange, typename OutputIterator, typename BinaryOperation, typename UnaryOperation,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR OutputIterator
		transform_inclusive_scan(InputRange const& rng, OutputIterator result, BinaryOperation binary_op, UnaryOperation unary_op) {
			return sprout::transform_inclusive_scan(sprout::begin(rng), sprout::end(rng), result, binary_op, unary_op);
		}
		template<
			typename InputRange, typename OutputIterator, typename BinaryOperation, typename UnaryOperation, typename T,
			typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR OutputIterator
		transform_inclusive_scan(InputRange const& rng, OutputIterator result, BinaryOperation binary_op, UnaryOperation unary_op, T init) {
			return sprout::transform_inclusive_scan(sprout::begin(rng), sprout::end(rng), result, binary_op, unary_op, init);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_CXX14_TRANSFORM_INCLUSIVE_SCAN_HPP
