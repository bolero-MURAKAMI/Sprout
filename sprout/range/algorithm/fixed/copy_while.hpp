/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_WHILE_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_WHILE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/copy_while.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy_while
			//
			template<
				typename InputRange, typename Result, typename Predicate,
				typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			copy_while(InputRange const& rng, Result const& result, Predicate pred) {
				return sprout::fixed::copy_while(sprout::begin(rng), sprout::end(rng), result, pred);
			}

			template<typename Result, typename InputRange, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			copy_while(InputRange const& rng, Predicate pred) {
				return sprout::fixed::copy_while<Result>(sprout::begin(rng), sprout::end(rng), pred);
			}
		}	// namespace fixed

		using sprout::range::fixed::copy_while;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_WHILE_HPP
