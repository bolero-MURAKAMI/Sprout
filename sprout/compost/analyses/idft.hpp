/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_ANALYSES_IDFT_HPP
#define SPROUT_COMPOST_ANALYSES_IDFT_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/idft.hpp>

namespace sprout {
	namespace compost {
		namespace analyses {
			//
			// idft
			//
			using sprout::adaptors::idft;
		}	// namespace analyses

		using sprout::compost::analyses::idft;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_ANALYSES_IDFT_HPP
