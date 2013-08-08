/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_SORT_HPP
#define SPROUT_ALGORITHM_FIXED_SORT_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/stable_sort.hpp>

namespace sprout {
	namespace fixed {
		//
		// sort
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		sort(Container const& cont, Compare comp) {
			return sprout::fixed::stable_sort(cont, comp);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		sort(Container const& cont) {
			return sprout::fixed::stable_sort(cont);
		}
	}	// namespace fixed

	using sprout::fixed::sort;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SORT_HPP
