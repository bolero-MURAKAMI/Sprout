#ifndef SPROUT_NONE_HPP
#define SPROUT_NONE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// none_t
	// none
	//
	struct none_t {};
	namespace {
		SPROUT_STATIC_CONSTEXPR none_t none = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_NONE_HPP
