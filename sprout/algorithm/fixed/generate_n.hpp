/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIXED_GENERATE_N_HPP
#define SPROUT_ALGORITHM_FIXED_GENERATE_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/generate.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	namespace fixed {
		//
		// generate_n
		//
		template<typename Container, typename Size, typename Generator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		generate_n(Container const& cont, Size n, Generator const& gen) {
			return sprout::fixed::detail::generate_impl(cont, gen, n);
		}

		template<typename Container, typename Size, typename Generator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		generate_n(Size n, Generator const& gen) {
			return sprout::fixed::generate_n(sprout::pit<Container>(), n, gen);
		}
	}	// namespace fixed

	template<
		typename Container, typename Size, typename Generator,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Container>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
	generate_n(Container const& cont, Size n, Generator const& gen) {
		return sprout::fixed::generate_n(cont, n, gen);
	}

	template<typename Container, typename Size, typename Generator>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
	generate_n(Size n, Generator const& gen) {
		return sprout::fixed::generate_n<Container>(n, gen);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_GENERATE_N_HPP
