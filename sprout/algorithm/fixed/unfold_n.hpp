/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_UNFOLD_N_HPP
#define SPROUT_ALGORITHM_FIXED_UNFOLD_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/unfold.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	namespace fixed {
		//
		// unfold_n
		//
		template<typename Container, typename Size, typename Generator, typename Init>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		unfold_n(Container const& cont, Size n, Generator const& gen, Init const& init) {
			return sprout::fixed::detail::unfold_impl(cont, gen, init, n);
		}

		template<typename Container, typename Size,typename Generator, typename Init>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		unfold_n(Size n, Generator const& gen, Init const& init) {
			return sprout::fixed::unfold_n(sprout::pit<Container>(), n, gen, init);
		}
	}	// namespace fixed

	using sprout::fixed::unfold_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_UNFOLD_N_HPP
