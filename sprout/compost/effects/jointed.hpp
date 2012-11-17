#ifndef SPROUT_COMPOST_EFFECTS_JOINTED_HPP
#define SPROUT_COMPOST_EFFECTS_JOINTED_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/jointed.hpp>

namespace sprout {
	namespace compost {
		namespace effects {
			//
			// jointed
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::adaptors::jointed_forwarder jointed{};
			}	// anonymous-namespace
		}	// namespace effects
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_JOINTED_HPP
