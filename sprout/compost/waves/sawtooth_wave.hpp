#ifndef SPROUT_COMPOST_WAVES_SAWTOOTH_WAVE_HPP
#define SPROUT_COMPOST_WAVES_SAWTOOTH_WAVE_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/sawtooth_wave.hpp>

namespace sprout {
	namespace compost {
		namespace waves {
			//
			// sawtooth_wave
			//
			namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::sawtooth_wave_forwarder sawtooth_wave{};
			}	// anonymous-namespace
		}	// namespace waves
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_WAVES_SAWTOOTH_WAVE_HPP
