#ifndef SPROUT_CINTTYPES_ABS_HPP
#define SPROUT_CINTTYPES_ABS_HPP

#include <cstdint>
#include <sprout/config.hpp>

namespace sprout {
	inline SPROUT_CONSTEXPR std::intmax_t
	imaxabs(std::intmax_t j) {
		return j < 0 ? -j : j;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CINTTYPES_ABS_HPP
