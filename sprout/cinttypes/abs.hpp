#ifndef SPROUT_CINTTYPES_ABS_HPP
#define SPROUT_CINTTYPES_ABS_HPP

#include <cstdint>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/enabler_if.hpp>

namespace sprout {
	SPROUT_CONSTEXPR std::intmax_t imaxabs(std::intmax_t j) {
		return j < 0 ? -j : j;
	}

	template<
		typename T,
		typename sprout::enabler_if<std::is_same<T, std::intmax_t>::value>::type = sprout::enabler
	>
	SPROUT_CONSTEXPR T abs(T j) {
		return sprout::imaxabs(j);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CINTTYPES_ABS_HPP
