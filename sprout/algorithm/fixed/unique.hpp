/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_UNIQUE_HPP
#define SPROUT_ALGORITHM_FIXED_UNIQUE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/unique_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// unique
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		unique(Container const& cont) {
			return sprout::fixed::unique_copy(sprout::begin(cont), sprout::end(cont), cont);
		}
		template<typename Container, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		unique(Container const& cont, BinaryPredicate pred) {
			return sprout::fixed::unique_copy(sprout::begin(cont), sprout::end(cont), cont, pred);
		}
	}	// namespace fixed

	using sprout::fixed::unique;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_UNIQUE_HPP
