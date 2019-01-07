/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_INPLACE_MERGE_HPP
#define SPROUT_ALGORITHM_FIXED_INPLACE_MERGE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/merge.hpp>

namespace sprout {
	namespace fixed {
		//
		// inplace_merge
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		inplace_merge(Container const& cont, typename sprout::container_traits<Container>::const_iterator middle, Compare comp) {
			return sprout::fixed::merge(
				sprout::begin(cont), middle,
				middle, sprout::end(cont),
				cont, comp
				);
		}
		//
		// inplace_merge
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		inplace_merge(Container const& cont, typename sprout::container_traits<Container>::const_iterator middle) {
			return sprout::fixed::merge(
				sprout::begin(cont), middle,
				middle, sprout::end(cont),
				cont
				);
		}
	}	// namespace fixed

	using sprout::fixed::inplace_merge;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_INPLACE_MERGE_HPP
