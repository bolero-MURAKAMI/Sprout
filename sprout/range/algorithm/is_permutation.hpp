/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_IS_PERMUTATION_HPP
#define SPROUT_RANGE_ALGORITHM_IS_PERMUTATION_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/is_permutation.hpp>

namespace sprout {
	namespace range {

		// 25.2.12 Is permutation
		template<typename ForwardRange1, typename ForwardRange2>
		inline SPROUT_CONSTEXPR bool
		is_permutation(ForwardRange1 const& range1, ForwardRange2 const& range2) {
			return sprout::is_permutation(sprout::begin(range1), sprout::end(range1), sprout::begin(range2));
		}

		template<typename ForwardRange1, typename ForwardRange2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR bool
		is_permutation(ForwardRange1 const& range1, ForwardRange2 const& range2, BinaryPredicate pred) {
			return sprout::is_permutation(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), pred);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_PERMUTATION_HPP
