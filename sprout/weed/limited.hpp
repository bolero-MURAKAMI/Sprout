/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_LIMITED_HPP
#define SPROUT_WEED_LIMITED_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace weed {
		//
		// limited
		//
		struct limited {
		public:
			enum category {
				discard,
				circular,
				stopover
			};
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_LIMITED_HPP
