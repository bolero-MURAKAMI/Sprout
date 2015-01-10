/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/remove_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// remove_copy
			//
			template<
				typename InputRange, typename Result, typename T,
				typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			remove_copy(InputRange const& rng, Result const& result, T const& value) {
				return sprout::fixed::remove_copy(sprout::begin(rng), sprout::end(rng), result, value);
			}

			template<typename Result, typename InputRange, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			remove_copy(InputRange const& rng, T const& value) {
				return sprout::fixed::remove_copy<Result>(sprout::begin(rng), sprout::end(rng), value);
			}
		}	// namespace fixed

		using sprout::range::fixed::remove_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_HPP
