/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIND_FIRST_OF_HPP
#define SPROUT_RANGE_ALGORITHM_FIND_FIRST_OF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/find_first_of.hpp>

namespace sprout {
	namespace range {

		// 25.2.7 Find first
		template<typename InputRange1, typename InputRange2>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<InputRange1>::type
		find_first_of(InputRange1&& range1, InputRange2&& range2) {
			return sprout::range::range_return<InputRange1>::pack(
				sprout::find_first_of(
					sprout::begin(SPROUT_FORWARD(InputRange1, range1)),
					sprout::end(SPROUT_FORWARD(InputRange1, range1)),
					sprout::begin(SPROUT_FORWARD(InputRange2, range2)),
					sprout::end(SPROUT_FORWARD(InputRange2, range2))
					),
				SPROUT_FORWARD(InputRange1, range1)
				);
		}

		template<typename InputRange1, typename InputRange2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<InputRange1>::type
		find_first_of(InputRange1&& range1, InputRange2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<InputRange1>::pack(
				sprout::find_first_of(
					sprout::begin(SPROUT_FORWARD(InputRange1, range1)),
					sprout::end(SPROUT_FORWARD(InputRange1, range1)),
					sprout::begin(SPROUT_FORWARD(InputRange2, range2)),
					sprout::end(SPROUT_FORWARD(InputRange2, range2)),
					pred
					),
				SPROUT_FORWARD(InputRange1, range1)
				);
		}

		template<sprout::range::range_return_value RetV, typename InputRange1, typename InputRange2>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<InputRange1, RetV>::type
		find_first_of(InputRange1&& range1, InputRange2&& range2) {
			return sprout::range::range_return<InputRange1, RetV>::pack(
				sprout::find_first_of(
					sprout::begin(SPROUT_FORWARD(InputRange1, range1)),
					sprout::end(SPROUT_FORWARD(InputRange1, range1)),
					sprout::begin(SPROUT_FORWARD(InputRange2, range2)),
					sprout::end(SPROUT_FORWARD(InputRange2, range2))
					),
				SPROUT_FORWARD(InputRange1, range1)
				);
		}

		template<sprout::range::range_return_value RetV, typename InputRange1, typename InputRange2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<InputRange1, RetV>::type
		find_first_of(InputRange1&& range1, InputRange2&& range2, BinaryPredicate pred) {
			return sprout::range::range_return<InputRange1, RetV>::pack(
				sprout::find_first_of(
					sprout::begin(SPROUT_FORWARD(InputRange1, range1)),
					sprout::end(SPROUT_FORWARD(InputRange1, range1)),
					sprout::begin(SPROUT_FORWARD(InputRange2, range2)),
					sprout::end(SPROUT_FORWARD(InputRange2, range2)),
					pred
					),
				SPROUT_FORWARD(InputRange1, range1)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIND_FIRST_OF_HPP
