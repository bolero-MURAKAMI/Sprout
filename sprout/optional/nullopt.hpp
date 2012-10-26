#ifndef SPROUT_OPTIONAL_NULLOPT_HPP
#define SPROUT_OPTIONAL_NULLOPT_HPP

#include <sprout/config.hpp>
#include <sprout/none.hpp>

namespace sprout {
	//
	// none_t
	// none
	//
	typedef sprout::none_t nullopt_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR nullopt_t nullopt{};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_NULLOPT_HPP
