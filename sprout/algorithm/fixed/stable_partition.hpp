/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_HPP
#define SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/stable_partition_copy.hpp>

namespace sprout {
	namespace fixed {
		//
		// stable_partition
		//
		template<typename Container, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		stable_partition(Container const& cont, Predicate pred) {
			return sprout::fixed::stable_partition_copy(sprout::begin(cont), sprout::end(cont), cont, pred);
		}
	}	// namespace fixed

	using sprout::fixed::stable_partition;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_STABLE_PARTITION_HPP
