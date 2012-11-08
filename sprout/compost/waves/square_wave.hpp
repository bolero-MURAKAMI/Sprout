#ifndef SPROUT_COMPOST_WAVES_SQUARE_WAVE_HPP
#define SPROUT_COMPOST_WAVES_SQUARE_WAVE_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/square_wave.hpp>

namespace sprout {
	namespace compost {
		namespace waves {
			//
			// square_wave
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::adaptors::square_wave_forwarder square_wave{};
			}	// anonymous-namespace
		}	// namespace waves
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_WAVES_SQUARE_WAVE_HPP
