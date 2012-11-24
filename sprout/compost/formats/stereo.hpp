#ifndef SPROUT_COMPOST_FORMATS_STEREO_HPP
#define SPROUT_COMPOST_FORMATS_STEREO_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/alternated.hpp>

namespace sprout {
	namespace compost {
		namespace formats {
			//
			// stereo
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::adaptors::alternated_forwarder stereo{};
			}	// anonymous-namespace
		}	// namespace formats

		using sprout::compost::formats::stereo;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_FORMATS_STEREO_HPP
