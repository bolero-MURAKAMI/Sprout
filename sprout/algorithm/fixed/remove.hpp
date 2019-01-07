/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_REMOVE_HPP
#define SPROUT_ALGORITHM_FIXED_REMOVE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/remove_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// remove
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		remove(Container const& cont, T const& value) {
			return sprout::fixed::remove_copy(sprout::begin(cont), sprout::end(cont), cont, value);
		}
	}	// namespace fixed

	using sprout::fixed::remove;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REMOVE_HPP
