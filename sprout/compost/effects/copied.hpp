#ifndef SPROUT_COMPOST_EFFECTS_COPIED_HPP
#define SPROUT_COMPOST_EFFECTS_COPIED_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/copied.hpp>

namespace sprout {
	namespace compost {
		namespace effects {
			//
			// copied
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::adaptors::copied_forwarder copied{};
			}	// anonymous-namespace
		}	// namespace effects
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_COPIED_HPP
