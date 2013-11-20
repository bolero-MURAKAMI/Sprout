/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_REPLACE_IF_HPP
#define SPROUT_ALGORITHM_FIXED_REPLACE_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/replace_copy_if.hpp>

namespace sprout {
	namespace fixed {
		//
		// replace_if
		//
		template<typename Container, typename Predicate, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		replace_if(Container const& cont, Predicate pred, T const& new_value) {
			return sprout::fixed::replace_copy_if(sprout::begin(cont), sprout::end(cont), cont, pred, new_value);
		}
	}	// namespace fixed

	using sprout::fixed::replace_if;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REPLACE_IF_HPP
