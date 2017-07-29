/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_REMOVE_IF_HPP
#define SPROUT_ALGORITHM_FIXED_REMOVE_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/remove_copy_if.hpp>

namespace sprout {
	namespace fixed {
		//
		// remove_if
		//
		template<typename Container, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		remove_if(Container const& cont, Predicate pred) {
			return sprout::fixed::remove_copy_if(sprout::begin(cont), sprout::end(cont), cont, pred);
		}
	}	// namespace fixed

	using sprout::fixed::remove_if;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REMOVE_IF_HPP
