/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_HPP
#define SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/swap_element_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// swap_element
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		swap_element(
			Container const& cont,
			typename sprout::container_traits<Container>::const_iterator pos1,
			typename sprout::container_traits<Container>::const_iterator pos2
			)
		{
			return sprout::fixed::swap_element_copy(sprout::begin(cont), sprout::end(cont), cont, pos1, pos2);
		}
	}	// namespace fixed

	using sprout::fixed::swap_element;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_HPP
