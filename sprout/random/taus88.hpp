/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_TAUS88_HPP
#define SPROUT_RANDOM_TAUS88_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/random/linear_feedback_shift.hpp>
#include <sprout/random/xor_combine.hpp>

namespace sprout {
	namespace random {
		//
		// taus88
		//
		typedef sprout::random::xor_combine_engine<
			sprout::random::xor_combine_engine<
				sprout::random::linear_feedback_shift_engine<std::uint32_t, 32, 31, 13, 12>,
				0,
				sprout::random::linear_feedback_shift_engine<std::uint32_t, 32, 29, 2, 4>,
				0
			>,
			0,
			sprout::random::linear_feedback_shift_engine<std::uint32_t, 32, 28, 3, 17>,
			0
		> taus88;
	}	// namespace random

	using sprout::random::taus88;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_TAUS88_HPP
