/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/reverse_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// reverse_copy
			//
			template<
				typename BidirectionalRange, typename Result,
				typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			reverse_copy(BidirectionalRange const& rng, Result const& result) {
				return sprout::fixed::reverse_copy(sprout::begin(rng), sprout::end(rng), result);
			}

			template<typename Result, typename BidirectionalRange>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			reverse_copy(BidirectionalRange const& rng) {
				return sprout::fixed::reverse_copy<Result>(sprout::begin(rng), sprout::end(rng));
			}
		}	// namespace fixed

		using sprout::range::fixed::reverse_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REVERSE_COPY_HPP
