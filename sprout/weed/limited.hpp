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
