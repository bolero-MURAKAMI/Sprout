/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIND_SYMMETRIC_DIFFERENCE_HPP
#define SPROUT_RANGE_ALGORITHM_FIND_SYMMETRIC_DIFFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/range/type_traits/lvalue_iterator.hpp>
#include <sprout/algorithm/find_symmetric_difference.hpp>

namespace sprout {
	namespace range {
		//
		// find_symmetric_difference
		//
		template<typename InputRange1, typename InputRange2, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::lvalue_iterator<InputRange1>::type,
			typename sprout::range::lvalue_iterator<InputRange2>::type
		>
		find_symmetric_difference(InputRange1&& range1, InputRange2&& range2, Compare comp) {
			return sprout::find_symmetric_difference(
				sprout::begin(SPROUT_FORWARD(InputRange1, range1)),
				sprout::end(SPROUT_FORWARD(InputRange1, range1)),
				sprout::begin(SPROUT_FORWARD(InputRange2, range2)),
				sprout::end(SPROUT_FORWARD(InputRange2, range2)),
				comp
				);
		}

		template<typename InputRange1, typename InputRange2>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::lvalue_iterator<InputRange1>::type,
			typename sprout::range::lvalue_iterator<InputRange2>::type
		>
		find_symmetric_difference(InputRange1&& range1, InputRange2&& range2) {
			return sprout::find_symmetric_difference(
				sprout::begin(SPROUT_FORWARD(InputRange1, range1)),
				sprout::end(SPROUT_FORWARD(InputRange1, range1)),
				sprout::begin(SPROUT_FORWARD(InputRange2, range2)),
				sprout::end(SPROUT_FORWARD(InputRange2, range2))
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIND_SYMMETRIC_DIFFERENCE_HPP
