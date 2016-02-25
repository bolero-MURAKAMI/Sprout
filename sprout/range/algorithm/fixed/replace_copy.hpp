/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/replace_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// replace_copy
			//
			template<
				typename InputRange, typename Result, typename T,
				typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			replace_copy(InputRange const& rng, Result const& result, T const& old_value, T const& new_value) {
				return sprout::fixed::replace_copy(sprout::begin(rng), sprout::end(rng), result, old_value, new_value);
			}

			template<typename Result, typename InputRange, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			replace_copy(InputRange const& rng, T const& old_value, T const& new_value) {
				return sprout::fixed::replace_copy<Result>(sprout::begin(rng), sprout::end(rng), old_value, new_value);
			}
		}	// namespace fixed

		using sprout::range::fixed::replace_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_HPP
