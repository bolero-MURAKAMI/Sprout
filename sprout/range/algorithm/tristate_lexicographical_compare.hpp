/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_TRISTATE_LEXICOGRAPHICAL_COMPARE_HPP
#define SPROUT_RANGE_ALGORITHM_TRISTATE_LEXICOGRAPHICAL_COMPARE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>

namespace sprout {
	namespace range {
		//
		// tristate_lexicographical_compare
		//
		template<typename InputRange1, typename InputRange2>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare(InputRange1 const& range1, InputRange2 const& range2) {
			return sprout::tristate_lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2)
				);
		}

		template<typename InputRange1, typename InputRange2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare(InputRange1 const& range1, InputRange2 const& range2, Compare comp) {
			return sprout::tristate_lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2), comp
				);
		}

		template<typename InputRange1, typename T1, typename InputRange2, typename T2>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare(InputRange1 const& range1, T1 const& delim1, InputRange2 const& range2, T2 const& delim2) {
			return sprout::tristate_lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), delim1, sprout::begin(range2), sprout::end(range2), delim2
				);
		}

		template<typename InputRange1, typename T1, typename InputRange2, typename T2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare(InputRange1 const& range1, T1 const& delim1, InputRange2 const& range2, T2 const& delim2, Compare comp) {
			return sprout::tristate_lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), delim1, sprout::begin(range2), sprout::end(range2), delim2, comp
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_TRISTATE_LEXICOGRAPHICAL_COMPARE_HPP
