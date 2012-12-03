#ifndef SPROUT_COMPOST_ANALYSES_IDFT_HPP
#define SPROUT_COMPOST_ANALYSES_IDFT_HPP

#include <sprout/config.hpp>
#include <sprout/range/adaptor/idft.hpp>

namespace sprout {
	namespace compost {
		namespace analyses {
			//
			// idft
			//
			using sprout::adaptors::idft;
		}	// namespace analyses

		using sprout::compost::analyses::idft;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_ANALYSES_IDFT_HPP
