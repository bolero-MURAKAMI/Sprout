/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_ROTATE_HPP
#define SPROUT_ALGORITHM_FIXED_ROTATE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/rotate_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// rotate
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		rotate(Container const& cont, typename sprout::container_traits<Container>::const_iterator middle) {
			return sprout::fixed::rotate_copy(sprout::begin(cont), middle, sprout::end(cont), cont);
		}
	}	// namespace fixed

	using sprout::fixed::rotate;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_ROTATE_HPP
