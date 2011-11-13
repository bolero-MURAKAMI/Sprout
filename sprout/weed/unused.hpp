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
