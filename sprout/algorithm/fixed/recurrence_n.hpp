/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_RECURRENCE_N_HPP
#define SPROUT_ALGORITHM_FIXED_RECURRENCE_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/recurrence.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	namespace fixed {
		//
		// recurrence_n
		//
		template<typename Container, typename Size, typename Generator, typename... Inits>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		recurrence_n(Container const& cont, Size n, Generator const& gen, Inits const&... inits) {
			return sprout::fixed::detail::recurrence_impl(cont, gen, n, inits...);
		}

		template<typename Container, typename Size, typename Generator, typename... Inits>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		recurrence_n(Size n, Generator const& gen, Inits const&... inits) {
			return sprout::fixed::recurrence_n(sprout::pit<Container>(), n, gen, inits...);
		}
	}	// namespace fixed

	using sprout::fixed::recurrence_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_RECURRENCE_N_HPP
