#ifndef SPROUT_COMPOST_WAVES_TRIANGLE_WAVE_HPP
#define SPROUT_COMPOST_WAVES_TRIANGLE_WAVE_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/triangle_wave.hpp>

namespace sprout {
	namespace compost {
		namespace waves {
			//
			// triangle_wave
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::adaptors::triangle_wave_forwarder triangle_wave{};
			}	// anonymous-namespace
		}	// namespace waves
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_WAVES_TRIANGLE_WAVE_HPP
