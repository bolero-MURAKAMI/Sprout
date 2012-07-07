#ifndef SPROUT_UTILITY_AS_LVALUE_HPP
#define SPROUT_UTILITY_AS_LVALUE_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// as_lvalue
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T&
	as_lvalue(T& t) {
		return t;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR T const&
	as_lvalue(T const& t) {
		return t;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_AS_LVALUE_HPP
