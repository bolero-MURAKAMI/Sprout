/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_RANDOM_RESULT_FWD_HPP
#define SPROUT_RANDOM_RANDOM_RESULT_FWD_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace random {
		//
		// random_result
		//
		template<typename Engine, typename Distribution = void, typename Enable = void>
		class random_result;
	}	// namespace random

	using sprout::random::random_result;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_RANDOM_RESULT_FWD_HPP
