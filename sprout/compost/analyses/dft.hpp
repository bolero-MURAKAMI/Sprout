/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_ANALYSES_DFT_HPP
#define SPROUT_COMPOST_ANALYSES_DFT_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/dft.hpp>

namespace sprout {
	namespace compost {
		namespace analyses {
			//
			// dft
			//
			using sprout::adaptors::dft;
		}	// namespace analyses

		using sprout::compost::analyses::dft;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_ANALYSES_DFT_HPP
