/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_STRING_FIXED_TO_UPPER_HPP
#define SPROUT_ALGORITHM_STRING_FIXED_TO_UPPER_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/string/fixed/to_upper_copy.hpp>

namespace sprout {
	namespace algorithm {
		namespace fixed {
			//
			// to_upper
			//
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
			to_upper(Container const& cont) {
				return sprout::algorithm::fixed::to_upper_copy(sprout::begin(cont), sprout::end(cont), cont);
			}
		}	// namespace fixed

		using sprout::algorithm::fixed::to_upper;
	}	// namespace algorithm

	namespace fixed {
		using sprout::algorithm::fixed::to_upper;
	}	// namespace fixed

	using sprout::algorithm::fixed::to_upper;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_STRING_FIXED_TO_UPPER_HPP
