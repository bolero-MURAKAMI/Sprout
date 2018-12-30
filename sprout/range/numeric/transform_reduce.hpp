/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_TRANSFORM_REDUCE_HPP
#define SPROUT_RANGE_NUMERIC_TRANSFORM_REDUCE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/transform_reduce.hpp>

namespace sprout {
	namespace range {

		// 29.8.5 Transform reduce
		template<typename InputRange1, typename InputRange2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR T
		transform_reduce(
			InputRange1 const& range1, InputRange2 const& range2,
			T init, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2
			)
		{
			return sprout::transform_reduce(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), init, binary_op1, binary_op2);
		}

		template<typename InputRange1, typename InputRange2, typename T>
		inline SPROUT_CONSTEXPR T
		transform_reduce(InputRange1 const& range1, InputRange2 const& range2, T init) {
			return sprout::transform_reduce(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), init);
		}

		template<typename InputRange, typename T, typename BinaryOperation, typename UnaryOperation>
		inline SPROUT_CONSTEXPR T
		transform_reduce(InputRange const& range, T init, BinaryOperation binary_op, UnaryOperation unary_op) {
			return sprout::transform_reduce(sprout::begin(range), sprout::end(range), init, binary_op, unary_op);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_TRANSFORM_REDUCE_HPP
