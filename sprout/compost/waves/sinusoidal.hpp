#ifndef SPROUT_COMPOST_WAVES_SINUSOIDAL_HPP
#define SPROUT_COMPOST_WAVES_SINUSOIDAL_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/sinusoidal.hpp>

namespace sprout {
	namespace compost {
		namespace waves {
			//
			// sinusoidal
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::adaptors::sinusoidal_forwarder sinusoidal{};
			}	// anonymous-namespace
		}	// namespace waves
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_WAVES_SINUSOIDAL_HPP
