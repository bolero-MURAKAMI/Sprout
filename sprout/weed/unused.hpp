/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_UNUSED_HPP
#define SPROUT_WEED_UNUSED_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace weed {
		//
		// unused
		//
		struct unused {
		public:
			unused() = default;
			template<typename T>
			SPROUT_CONSTEXPR unused(T) {}
			template<typename T>
			SPROUT_CONSTEXPR operator T() const {
				return T();
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_UNUSED_HPP
