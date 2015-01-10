/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIT_ROTATE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_ROTATE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/algorithm/fit/rotate_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// rotate_copy
			//
			template<typename ForwardRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			rotate_copy(
				ForwardRange const& rng, typename sprout::container_traits<ForwardRange>::const_iterator middle,
				Result const& result
				)
			{
				return sprout::fit::rotate_copy(sprout::begin(rng), middle, sprout::end(rng), result);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_ROTATE_COPY_HPP
