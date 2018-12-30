/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_DFT_CXX14_TRIANGLE_HPP
#define SPROUT_RANGE_NUMERIC_DFT_CXX14_TRIANGLE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/numeric/dft/cxx14/triangle.hpp>

namespace sprout {
	namespace range {
		//
		// triangle
		//
		template<typename ForwardRange>
		inline SPROUT_CXX14_CONSTEXPR void
		triangle(
			ForwardRange&& rng,
			typename sprout::container_traits<ForwardRange>::value_type const& frequency = 1,
			typename sprout::container_traits<ForwardRange>::value_type const& amplitude = 1,
			typename sprout::container_traits<ForwardRange>::value_type const& phase = 0,
			typename sprout::container_traits<ForwardRange>::value_type const& duty = 0.5
			)
		{
			sprout::triangle(
				sprout::begin(SPROUT_FORWARD(ForwardRange, rng)), sprout::end(SPROUT_FORWARD(ForwardRange, rng)),
				frequency, amplitude, phase, duty
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_CXX14_TRIANGLE_HPP
