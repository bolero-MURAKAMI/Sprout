/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_STRING_FIXED_TO_LOWER_HPP
#define SPROUT_ALGORITHM_STRING_FIXED_TO_LOWER_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/string/fixed/to_lower_copy.hpp>

namespace sprout {
	namespace algorithm {
		namespace fixed {
			//
			// to_lower
			//
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			to_lower(Container const& cont) {
				return sprout::algorithm::fixed::to_lower_copy(sprout::begin(cont), sprout::end(cont), cont);
			}
		}	// namespace fixed

		using sprout::algorithm::fixed::to_lower;
	}	// namespace algorithm

	namespace fixed {
		using sprout::algorithm::fixed::to_lower;
	}	// namespace fixed

	using sprout::algorithm::fixed::to_lower;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_STRING_FIXED_TO_LOWER_HPP
