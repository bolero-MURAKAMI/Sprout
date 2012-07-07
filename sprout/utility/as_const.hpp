#ifndef SPROUT_UTILITY_AS_CONST_HPP
#define SPROUT_UTILITY_AS_CONST_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// as_const
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::conditional<
		std::is_lvalue_reference<T>::value,
		typename std::remove_reference<T>::type const&,
		typename std::remove_reference<T>::type const&&
	>::type
	as_const(T&& t) {
		return sprout::forward<T>(t);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_AS_CONST_HPP
