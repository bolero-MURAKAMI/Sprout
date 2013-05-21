#ifndef SPROUT_OPTIONAL_IN_PLACE_HPP
#define SPROUT_OPTIONAL_IN_PLACE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// in_place_t
	// in_place
	//
	struct in_place_t {};
	namespace {
		SPROUT_STATIC_CONSTEXPR in_place_t in_place{};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_IN_PLACE_HPP
