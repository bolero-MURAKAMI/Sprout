/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_REDUCE_HPP
#define SPROUT_RANGE_NUMERIC_REDUCE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/reduce.hpp>

namespace sprout {
	namespace range {

		// 29.8.3 Reduce
		template<typename InputRange, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR T
		reduce(InputRange const& range, T init, BinaryOperation binary_op) {
			return sprout::reduce(sprout::begin(range), sprout::end(range), init, binary_op);
		}

		template<typename InputRange, typename T>
		inline SPROUT_CONSTEXPR T
		reduce(InputRange const& range, T init) {
			return sprout::reduce(sprout::begin(range), sprout::end(range), init);
		}

		template<typename InputRange>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<typename sprout::container_traits<InputRange>::iterator>::value_type
		reduce(InputRange const& range) {
			return sprout::reduce(sprout::begin(range), sprout::end(range));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_REDUCE_HPP
