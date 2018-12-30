/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_REPLACE_HPP
#define SPROUT_ALGORITHM_FIXED_REPLACE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/replace_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// replace
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		replace(Container const& cont, T const& old_value, T const& new_value) {
			return sprout::fixed::replace_copy(sprout::begin(cont), sprout::end(cont), cont, old_value, new_value);
		}
	}	// namespace fixed

	using sprout::fixed::replace;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REPLACE_HPP
