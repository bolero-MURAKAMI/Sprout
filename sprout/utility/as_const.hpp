#ifndef SPROUT_UTILITY_AS_CONST_HPP
#define SPROUT_UTILITY_AS_CONST_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// as_const
	//
	template<typename T>
	inline T const& as_const(T& t) {
		return t;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR T const& as_const(T const& t) {
		return t;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_AS_CONST_HPP
