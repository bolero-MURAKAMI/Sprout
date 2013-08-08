/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
#define SPROUT_RANGE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/lexicographical_compare.hpp>

namespace sprout {
	namespace range {

		// 25.4.8 Lexicographical comparison
		template<typename InputRange1, typename InputRange2>
		inline SPROUT_CONSTEXPR bool
		lexicographical_compare(InputRange1 const& range1, InputRange2 const& range2) {
			return sprout::lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2)
				);
		}

		template<typename InputRange1, typename InputRange2, typename Compare>
		inline SPROUT_CONSTEXPR bool
		lexicographical_compare(InputRange1 const& range1, InputRange2 const& range2, Compare comp) {
			return sprout::lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2), comp
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
